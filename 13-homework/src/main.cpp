#include <iostream>
#include <stdexcept>
#include <filesystem>

#include <boost/program_options.hpp>

#include "../lib/headers/AccuracyFinder.h"

struct InputStruct
{
    std::filesystem::path model_src;
    std::filesystem::path test_src;
    std::size_t input_dim;
    std::size_t hidden_dim;
    std::size_t output_dim;
};

InputStruct ParseCommandOptions(int argc, char* argv[])
{
    namespace po = boost::program_options;
    po::options_description commamdsDescription("Available commands");
    commamdsDescription.add_options()
        ("help", "Print this message")
        ("model_src", po::value<std::string>()->required(), "< path to w.txt files :3 >")
        ("test_src", po::value<std::string>()->required(), "< path to csv file >")
        ("input_dim", po::value<std::size_t>()->required()->default_value(784), "<int>")
        ("hidden_dim", po::value<std::size_t>()->required()->default_value(128), "<int>")
        ("output_dim", po::value<std::size_t>()->required()->default_value(10), "<int>")
    ;

    po::variables_map varMap;
    try
    {
        auto parsed = po::command_line_parser(argc, argv)
            .options(commamdsDescription)
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

    std::filesystem::path model_src = varMap["model_src"].as<std::string>();
    std::filesystem::path test_src = varMap["test_src"].as<std::string>();
    std::size_t input_dim = varMap["input_dim"].as<std::size_t>();
    std::size_t hidden_dim = varMap["hidden_dim"].as<std::size_t>();
    std::size_t output_dim = varMap["output_dim"].as<std::size_t>();

    return InputStruct{model_src, test_src, input_dim, hidden_dim, output_dim};
}

int main(int argc, char* argv[]) try
{
    std::ios::sync_with_stdio(false);

    InputStruct context;
    context = ParseCommandOptions(argc, argv);

    AccuracyFinder af(context.input_dim, context.hidden_dim, context.output_dim);
    af.SetupClassifier(context.model_src);
    std::cout << af.GetAccuracy(context.test_src) << std::endl;
}
catch (const std::exception& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
