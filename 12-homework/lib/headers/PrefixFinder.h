#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <future>
#include <filesystem>
#include <iostream>

#include "ThreadPool.h"

class PrefixFinder
{
public:
    PrefixFinder() = default;
    ~PrefixFinder() = default;

    int FindMinimumPossiblePrefixUnambiguousIdentifyingString(const std::filesystem::path &pathToFolder, std::size_t filesCount)
    {
        using finder_result = std::future<int>;

        ThreadPool finder_workers(filesCount);
        std::vector<finder_result> prefixes(filesCount);

        for (std::size_t i = 0; i < filesCount; ++i)
        {
            auto finder_job = [i, &prefixes, &pathToFolder]() -> int
            {
                std::ifstream file(pathToFolder / ("output/result" + std::to_string(i) + ".txt"));
                std::vector<std::string> strings;
                std::size_t minStringLenght = SIZE_MAX;
                std::size_t prefix = 1;

                std::string line;
                while (std::getline(file, line))
                {
                    strings.emplace_back(line);
                    if (line.size() < minStringLenght)
                        minStringLenght = line.size();
                }

                for (; prefix <= minStringLenght; ++prefix)
                {
                    std::string tmp = strings.front();
                    for (auto &str : strings)
                        if (tmp.substr(0, prefix) != str.substr(0, prefix))
                            return prefix;
                }

                if (prefix == minStringLenght)
                    return -1;
            };

            prefixes[i] = finder_workers.enqueue(finder_job);
        }

        int prefix = 0;
        for (finder_result &res : prefixes)
        {
            int tmp = res.get();
            if (tmp > prefix)
                prefix = tmp;
        }
        return prefix;
    }
};
