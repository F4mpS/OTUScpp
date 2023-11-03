#pragma once

#include <unordered_map>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>
#include <regex>

#include "FilePathHasherator.h"
#include "interfaces/IFileParser.h"

class MaskFileParser : public IFileParser
{
public:
    using FileList = IFileParser::FileList;

    MaskFileParser(bool recursive) : recursive(recursive) {}
    virtual ~MaskFileParser() = default;

    FileList GetFileList() const override
    {
        if (!wasRun)
        {
            for (const auto &[path, iterator] : rootDirectories)
                if (CheckDirectory(path))
                    CrawlDirectory(iterator, fileList);
            wasRun = true;
        }
        return fileList;
    }

    void AddRootDirectory(const std::filesystem::path &rootDirectory)
    {
        if (rootDirectories.find(rootDirectory) != rootDirectories.end())
            return;

        std::filesystem::path normal_path = rootDirectory.lexically_normal();

        if (recursive)
        {
            for (auto it = rootDirectories.begin(); it != rootDirectories.end();)
            {
                const std::filesystem::path &path = it->first;
                auto [first, second] = std::mismatch(path.begin(), path.end(), normal_path.begin(), normal_path.end());
                if (first == path.end())
                    return;
                if (second == normal_path.end())
                    it = rootDirectories.erase(it);
                else
                    ++it;
                (void)second;
            }
        }

        Reset();

        std::filesystem::directory_iterator directoryIter(normal_path);
        rootDirectories.emplace(normal_path, directoryIter);
    }

    void ExcludeDirectory(const std::filesystem::path &excludedDirectory)
    {
        Reset();
        excludedDirectories.emplace_back(excludedDirectory.lexically_normal());
    }

    void IncludeFileMask(std::regex fileMask)
    {
        Reset();
        includedFileMasks.emplace_back(fileMask);
    }

    void ExcludeFileMask(std::regex fileMask)
    {
        Reset();
        excludedFileMasks.emplace_back(fileMask);
    }

    void SetMinFileSize(std::size_t fileSize)
    {
        Reset();
        minFileSize = fileSize;
    }

private:
    void CrawlDirectory(const std::filesystem::directory_iterator &directoryIter, FileList &fileList) const
    {
        for (const std::filesystem::directory_entry &entry : directoryIter)
        {
            if (entry.is_regular_file() && CheckFile(entry.path()))
                fileList.emplace_back(entry.path());
            else if (recursive && entry.is_directory() && CheckDirectory(entry.path()))
                CrawlDirectory(std::filesystem::directory_iterator(entry.path()), fileList);
        }
    }

    bool CheckDirectory(const std::filesystem::path &directory) const
    {
        return std::find(excludedDirectories.begin(), excludedDirectories.end(), directory) == excludedDirectories.end();
    }

    bool CheckFile(const std::filesystem::path &file) const
    {
        if (minFileSize != 0)
        {
            std::ifstream::pos_type fileSize = std::ifstream(file, std::ios::in | std::ios::binary | std::ios::ate).tellg();
            if (fileSize == -1 || static_cast<std::size_t>(fileSize) < minFileSize)
                return false;
        }

        if (includedFileMasks.empty())
            return true;

        for (const std::regex &regex : excludedFileMasks)
            if (std::regex_match(file.string(), regex))
                return false;

        for (const std::regex &regex : includedFileMasks)
            if (std::regex_match(file.string(), regex))
                return true;

        return false;
    }

    void Reset()
    {
        wasRun = false;
        fileList.clear();
        for (auto &[path, iterator] : rootDirectories)
            iterator = std::filesystem::directory_iterator(path);
    }

    struct RootDirectory
    {
        RootDirectory(std::filesystem::path path, std::filesystem::directory_iterator iterator) : path(path), iterator(iterator) {}

        std::filesystem::path path;
        std::filesystem::directory_iterator iterator;
    };

    std::unordered_map<std::filesystem::path, std::filesystem::directory_iterator, FilePathHasherator> rootDirectories;
    std::vector<std::filesystem::path> excludedDirectories;
    std::vector<std::regex> includedFileMasks;
    std::vector<std::regex> excludedFileMasks;

    std::size_t minFileSize = 0;

    mutable FileList fileList;
    mutable bool wasRun = false;

    const bool recursive;
};
