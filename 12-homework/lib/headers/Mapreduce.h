#pragma once

#include <vector>
#include <map>
#include <utility>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "Block.h"
#include "Maper.h"
#include "Reducer.h"

class MapReduce
{
public:
    MapReduce(int m_count, int r_count) : mappers_count(m_count), reducers_count(r_count) {}
    ~MapReduce() = default;

    void run(const std::filesystem::path &input)
    {
        auto blocks = SplitFile(input, mappers_count);

        Maper maper;
        maper.Mapping(blocks, input);

        auto mapped = maper.GetMappedData();
        auto shuffled = ShuffleMapped(mapped);

        Reducer reducer;
        reducer.Reduce(shuffled, input);
    }

private:
    std::vector<Block> SplitFile(const std::filesystem::path &filePath, int blocksCount)
    {
        auto fileName = filePath.native();

        std::ifstream::pos_type size = std::ifstream(fileName, std::ios::in | std::ios::ate).tellg();

        std::ptrdiff_t step = size / blocksCount;
        std::vector<Block> blocks(blocksCount);
        std::ifstream::pos_type prev = 0, next;

        std::ifstream file(fileName);

        for (std::size_t i = 0; i < blocksCount; ++i)
        {
            next = (size - prev < step ? size : prev + step);
            file.seekg(next);
            while (next < size && file.peek() != '\n')
            {
                next += 1;
                file.ignore(1);
            }
            blocks[i].from = prev;
            blocks[i].to = next;
            prev = next;
            if (prev != size)
                prev += 1;
        }

        return blocks;
    }

    using dataANDdataDuplicatesCount = std::map<std::string, std::size_t>;
    using dataContainer = std::pair<dataANDdataDuplicatesCount, std::size_t>;

    std::vector<std::vector<std::string>> ShuffleMapped(std::vector<std::vector<std::string>> mapped)
    {
        std::vector<dataContainer> shuffled(reducers_count);

        for (auto &data : mapped)
            for (auto str : data)
                PushToShuffled(str, shuffled);

        std::vector<std::vector<std::string>> result;
        for (auto &dataCont : shuffled)
        {
            std::vector<std::string> tmp;

            PushDataToVector(dataCont, tmp);

            result.emplace_back(tmp);
        }

        return result;
    }

    void PushToShuffled(std::string str, std::vector<dataContainer> &container)
    {
        bool isNew = 1;
        for (auto &data : container)
        {
            if (data.first.count(str))
            {
                isNew = 0;
                data.first[str] += 1;
            }
        }

        if (isNew)
        {
            dataContainer *dataWithMinSize = &container.back();

            for (auto &data : container)
            {
                if (data.second < dataWithMinSize->second)
                    dataWithMinSize = &data;
            }

            dataWithMinSize->first.insert({str, 1});
            dataWithMinSize->second += 1;
        }
    }

    void PushDataToVector(const dataContainer &data, std::vector<std::string> &container)
    {
        for (auto &map : data.first)
        {
            for (size_t i = 0; i < map.second; i++)
                container.emplace_back(map.first);
        }
    }

    int mappers_count;
    int reducers_count;
};