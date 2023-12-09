#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include "ThreadPool.h"

class Reducer
{
public:
    Reducer() = default;
    ~Reducer() = default;

    void Reduce(std::vector<std::vector<std::string>> mapped, const std::filesystem::path &filePath, std::string fileName = "result")
    {
        std::filesystem::path outputFolder = filePath.parent_path() / "output";
        std::filesystem::create_directory(outputFolder);

        ThreadPool reducer_workers(mapped.size());

        for (std::size_t i = 0; i < mapped.size(); ++i)
        {
            auto reducer_job = [i, &mapped, &outputFolder, &fileName]() -> void
            {
                std::ofstream outFile(outputFolder / (fileName + std::to_string(i) + ".txt"));
                for (auto &str : mapped[i])
                {
                    outFile << str << std::endl;
                }
            };
            reducer_workers.enqueue(reducer_job);
        }
    }
};
