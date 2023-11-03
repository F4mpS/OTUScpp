#include <iostream>
#include <filesystem>
#include <regex>
#include <boost/program_options.hpp>

#include "../lib/MaskFileParser.h"
#include "../lib/BayanFileParser.h"
#include "../lib/hashes/CRC32.h"

namespace po = boost::program_options;

template <typename Hash>
void Start(std::size_t blockSize, IFileParser* fileParser)
{
    BayanFileParser<Hash> bayanParser(blockSize);
    bayanParser.AddFileParser(fileParser);

    std::vector<std::vector<std::filesystem::path>> equal = bayanParser.GetBayans();
    for (const std::vector<std::filesystem::path>& paths : equal)
    {
        for (const std::filesystem::path& path : paths)
            std::cout << path << '\n';
        std::cout << '\n';
    }
}

int main(int argc, char* argv[]) try
{
    po::options_description optDesc("Commands list");
    bool recursive = false;
    bool case_sensitive = false;
    optDesc.add_options()
        ("help",                                                                            "Print commands list")
        ("block_size",           po::value<std::size_t>()->required()->default_value(1024),       "Block size (bytes) used to compare files")
        ("hash",           po::value<std::string>()->required()->default_value("crc32"),    "Hash algorithm used to compare byte blocks (crc32)")
        ("file_min_size",  po::value<std::size_t>()->required()->default_value(1),          "Minimum file size (bytes) to compare")
        ("root_dir",       po::value<std::vector<std::string>>()->required()->multitoken(), "Directories to search bayans into")
        ("exclude_dir",    po::value<std::vector<std::string>>()->multitoken(),             "Direcroties to exclude from search")
        ("mask_include",   po::value<std::vector<std::string>>()->multitoken(),             "Include only files corresponding to these masks in search")
        ("mask_exclude",   po::value<std::vector<std::string>>()->multitoken(),             "Exclude files corresponding to these masks from search")
        ("recursive",      po::bool_switch(&recursive),                                     "Use this command to enable recursive subdirectory scanning")
        ("case_sensitive", po::bool_switch(&case_sensitive),                                "Use this command to make file masks case sensitive")
    ;

    po::variables_map varMap;
    try
    {
        auto parsed = po::command_line_parser(argc, argv)
            .options(optDesc)
            .run();
        po::store(parsed, varMap);
        if (varMap.count("help") != 0)
        {
            std::cout << optDesc << "\n";
            return 0;
        }
        po::notify(varMap);
    }
    catch (const po::error& error)
    {
        std::cerr << "Error while parsing command-line arguments: "
                  << error.what() << "\nPlease use --help to see help message\n";
        return 1;
    }

    std::size_t blockSize = varMap["block_size"].as<std::size_t>();
    if (blockSize == 0)
    {
        std::cerr << "Block size must be at least 1\n";
        return 1;
    }
    std::size_t minFileSize = varMap["file_min_size"].as<std::size_t>();

    std::vector<std::string> rootDirectories    = varMap["root_dir"].as<std::vector<std::string>>();

    std::vector<std::string> excludedDirectories = varMap.count("exclude_dir") == 0
                                                   ? std::vector<std::string>()
                                                   : varMap["exclude_dir"].as<std::vector<std::string>>();

    std::vector<std::string> includedMasks       = varMap.count("mask_include") == 0
                                                   ? std::vector<std::string>()
                                                   : varMap["mask_include"].as<std::vector<std::string>>();

    std::vector<std::string> excludedMasks       = varMap.count("mask_exclude") == 0
                                                   ? std::vector<std::string>()
                                                   : varMap["mask_exclude"].as<std::vector<std::string>>();

    MaskFileParser fileParser(recursive);

    for (std::string& root_directory : rootDirectories)
        fileParser.AddRootDirectory(std::filesystem::path(std::move(root_directory)));
    for (std::string& exclude_directory : excludedDirectories)
        fileParser.ExcludeDirectory(std::filesystem::path(std::move(exclude_directory)));

    std::regex::flag_type re_flags = (case_sensitive ? std::regex_constants::ECMAScript : std::regex_constants::icase);
    for (const std::string& mask_include : includedMasks)
        fileParser.IncludeFileMask(std::regex(mask_include, re_flags));
    for (const std::string& mask_exclude : excludedMasks)
        fileParser.ExcludeFileMask(std::regex(mask_exclude, re_flags));

    fileParser.SetMinFileSize(minFileSize);

    std::string hash_algo = varMap["hash"].as<std::string>();

    if (hash_algo == "crc32")
        Start<CRC32>(blockSize, &fileParser);
}
catch (const std::exception& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}