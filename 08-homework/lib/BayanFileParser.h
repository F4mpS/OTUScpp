#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <filesystem>
#include <optional>
#include <tuple>
#include <string>
#include <cassert>
#include <fstream>
#include <map>

#include "FilePathHasherator.h"
#include "interfaces/IFileParser.h"

template <typename Hash>
class BayanFileParser
{
public:
    BayanFileParser(std::size_t blockSize) : hasherator(Hash()), blockSize(blockSize) {}

    void AddFileParser(const IFileParser *fileParser)
    {
        fileParsers.emplace_back(fileParser);
        for (std::filesystem::path &path : fileParser->GetFileList())
            files.emplace(path, File());
    }

    std::vector<std::vector<std::filesystem::path>> GetBayans()
    {
        std::map<std::vector<std::size_t>, std::unordered_set<std::filesystem::path, FilePathHasherator>> byEqualHash;
        for (auto it = files.begin(); it != files.end() && std::next(it) != files.end(); ++it)
        {
            if (!it->second.canRead)
                continue;

            for (auto jt = std::next(it); jt != files.end(); ++jt)
            {
                if (!jt->second.canRead)
                    continue;

                auto openFile = [](const std::filesystem::path &path, File &file)
                {
                    if (file.stream == std::nullopt)
                    {
                        file.fileSize = std::ifstream(path, std::ios::in | std::ios::binary | std::ios::ate).tellg();
                        file.stream = std::ifstream(path, std::ios::in | std::ios::binary);
                    }
                    else
                    {
                        file.stream->open(path, std::ios::in | std::ios::binary);
                        file.stream->seekg(file.currPos);
                    }
                };

                openFile(it->first, it->second);
                openFile(jt->first, jt->second);

                if (!it->second.stream->is_open())
                {
                    it->second.canRead = false;
                    break;
                }
                if (!jt->second.stream->is_open())
                {
                    jt->second.canRead = false;
                    continue;
                }

                if (CompareFiles(it, jt))
                {
                    auto &paths = byEqualHash[it->second.blocksHash];
                    paths.emplace(it->first);
                    paths.emplace(jt->first);
                }

                auto closeFile = [](File &file)
                {
                    file.currPos = file.stream->tellg();
                    file.stream->close();
                };

                closeFile(it->second);
                closeFile(jt->second);
            }
        }

        std::vector<std::vector<std::filesystem::path>> ans;
        for (auto &[_, equalGroup] : byEqualHash)
        {
            ans.emplace_back(std::vector<std::filesystem::path>{});
            ans.back().reserve(equalGroup.size());
            for (typename decltype(equalGroup)::iterator it = equalGroup.begin(), next; it != equalGroup.end(); it = next)
            {
                next = std::next(it);
                ans.back().emplace_back(equalGroup.extract(it).value());
            }
        }

        return ans;
    }

private:
    struct File
    {
        std::vector<std::size_t> blocksHash;
        std::optional<std::ifstream> stream = std::nullopt;
        std::ifstream::pos_type fileSize = 0;
        std::ifstream::pos_type currPos = 0;
        bool canRead = true;
    };

    using FileIter = typename std::unordered_map<std::filesystem::path, File, FilePathHasherator>::iterator;

    std::string ReadBlock(std::ifstream &file)
    {
        std::string s(blockSize, '\0');
        file.read(s.data(), blockSize);
        return s;
    }

    bool CompareFiles(FileIter first, FileIter second)
    {
        if (first->second.fileSize != second->second.fileSize)
            return false;

        File *file1, *file2;

        if (first->second.blocksHash.size() > second->second.blocksHash.size())
        {
            file1 = &(first->second);
            file2 = &(second->second);
        }
        else
        {
            file1 = &(second->second);
            file2 = &(first->second);
        }

        for (std::size_t i = 0; i < file2->blocksHash.size(); ++i)
            if (file1->blocksHash[i] != file2->blocksHash[i])
                return false;

        std::string block2;
        while (file2->blocksHash.size() < file1->blocksHash.size())
        {
            block2 = ReadBlock(file2->stream.value());
            file2->blocksHash.emplace_back(hasherator(block2.data(), block2.size()));
            if (file2->blocksHash.back() != file1->blocksHash[file2->blocksHash.size() - 1])
                return false;
        }

        std::string block1;
        while (!IsEnded(*file1))
        {
            block1 = ReadBlock(file1->stream.value());
            block2 = ReadBlock(file2->stream.value());
            file1->blocksHash.emplace_back(hasherator(block1.data(), block1.size()));
            file2->blocksHash.emplace_back(hasherator(block2.data(), block2.size()));
            if (file2->blocksHash.back() != file1->blocksHash.back())
                return false;
        }

        return true;
    }

    bool IsEnded(File &file)
    {
        if (!file.stream->is_open())
            return true;
        std::ifstream::pos_type p = file.stream->tellg();
        return (p == std::ifstream::pos_type(-1) || p == file.fileSize);
    }

    Hash hasherator;
    std::vector<const IFileParser *> fileParsers;
    std::unordered_map<std::filesystem::path, File, FilePathHasherator> files;
    const std::size_t blockSize;
};
