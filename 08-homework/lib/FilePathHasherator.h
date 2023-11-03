#pragma once

#include <filesystem>

struct FilePathHasherator
{
    FilePathHasherator() = default;
    ~FilePathHasherator() = default;

    std::size_t operator()(const std::filesystem::path &path) const
    {
        return std::filesystem::hash_value(path);
    }
};
