#include <iostream>
#include <stdexcept>
#include <filesystem>

#include <boost/program_options.hpp>

#include "../lib/headers/Mapreduce.h"
#include "../lib/headers/PrefixFinder.h"

struct InputStruct
{
    std::filesystem::path path;
    std::size_t mnum;
    std::size_t rnum;
};

InputStruct ParseCommandOptions(int argc, char* argv[])
{
    namespace po = boost::program_options;
    po::options_description commamdsDescription("Available commands");
    commamdsDescription.add_options()
        ("help", "Print this message")
        ("src", po::value<std::string>()->required(), "<path to source file>")
        ("mnum", po::value<std::size_t>()->required(), "<int>")
        ("rnum", po::value<std::size_t>()->required(), "<int>")
    ;
    po::positional_options_description commamdsOptDescription;
    commamdsOptDescription.add("src", 1);
    commamdsOptDescription.add("mnum", 2);
    commamdsOptDescription.add("rnum", 3);

    po::variables_map varMap;
    try
    {
        auto parsed = po::command_line_parser(argc, argv)
            .options(commamdsDescription)
            .positional(commamdsOptDescription)
            .run();
        po::store(parsed, varMap);
        if (varMap.count("help") != 0)
        {
            std::cout << commamdsDescription << "\n";
            throw std::exception{};
        }
        po::notify(varMap);
    }
    catch (const po::error& error)
    {
        std::cerr << "Error while parsing command-line arguments: "
                  << error.what() << "\nPlease use --help to see help message\n";
        throw std::exception{};
    }

    std::filesystem::path path = varMap["src"].as<std::string>();
    std::size_t mnum = varMap["mnum"].as<std::size_t>();
    std::size_t rnum = varMap["rnum"].as<std::size_t>();

    return InputStruct{path, mnum, rnum};
}

int main(int argc, char* argv[]) try
{
    std::ios::sync_with_stdio(false);

    InputStruct context;
    context = ParseCommandOptions(argc, argv);

    MapReduce worker(context.mnum, context.rnum);
    worker.run(context.path);

    PrefixFinder finder;
    std::cout << finder.FindMinimumPossiblePrefixUnambiguousIdentifyingString(context.path.parent_path(), context.rnum) << std::endl;
}
catch (const std::exception& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
