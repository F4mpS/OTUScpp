#pragma once

#include <vector>
#include <filesystem>

class IFileParser
{
public:
    using FileList = std::vector<std::filesystem::path>;

    virtual FileList GetFileList() const = 0;

    virtual ~IFileParser() = default;
};
