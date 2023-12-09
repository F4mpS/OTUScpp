#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <future>
#include <filesystem>
#include <algorithm>

#include "Block.h"
#include "ThreadPool.h"

class MaperImplementation
{
public:
    MaperImplementation(const Block &dataBlock, const std::filesystem::path &filePath)
    {
        this->dataBlock = dataBlock;
        this->filePath = filePath;
    }

    std::string GetStringBlock()
    {
        std::ifstream file(filePath.native());
        file.seekg(dataBlock.from);
        std::string stringBlock(dataBlock.to - dataBlock.from, '\0');
        file.read(stringBlock.data(), dataBlock.to - dataBlock.from);

        return stringBlock;
    }

    std::vector<std::string> operator()()
    {
        std::string all = GetStringBlock();
        std::string line;
        std::istringstream stream(all);
        std::vector<std::string> ans;
        while (std::getline(stream, line))
        {
            ans.emplace_back(line);
        }
        std::sort(ans.begin(), ans.end());

        return ans;
    }

    Block dataBlock;
    std::filesystem::path filePath;
};

class Maper
{
public:
    Maper() = default;
    ~Maper() = default;

    void Mapping(const std::vector<Block> &blocks, const std::filesystem::path &filePath)
    {
        using maper_result = std::future<std::vector<std::string>>;

        std::vector<maper_result> mapped(blocks.size());
        ThreadPool mapper_workers(blocks.size());

        for (std::size_t i = 0; i < blocks.size(); ++i)
        {
            auto mapper_job = [i, &blocks, &filePath]() -> std::vector<std::string>
            {
                MaperImplementation maperImp(blocks[i], filePath);
                return maperImp();
            };
            mapped[i] = mapper_workers.enqueue(mapper_job);
        }

        for (maper_result &future_result : mapped)
        {
            mapped_data.emplace_back(future_result.get());
        }
    }

    std::vector<std::vector<std::string>> GetMappedData()
    {
        return mapped_data;
    }

private:
    std::vector<std::vector<std::string>> mapped_data;
};
