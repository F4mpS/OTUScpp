#include <iostream>
#include <stdexcept>

#include <boost/program_options.hpp>
#include <boost/asio.hpp>

#include "../lib/headers/network/Server.h"

struct PortStruct
{
    std::size_t port;
};

PortStruct ParseCommandOptions(int argc, char* argv[])
{
    namespace po = boost::program_options;
    po::options_description commamdsDescription("Available commands");
    commamdsDescription.add_options()
        ("help", "Print this message")
        ("port", po::value<std::size_t>()->required(), "<port>")
    ;
    po::positional_options_description commamdsOptDescription;
    commamdsOptDescription.add("port", 1);

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

    std::size_t port = varMap["port"].as<std::size_t>();

    return PortStruct{port};
}

int main(int argc, char* argv[]) try
{
    std::ios::sync_with_stdio(false);

    PortStruct context;
    context = ParseCommandOptions(argc, argv);

    boost::asio::io_service io_context;

    Server server(io_context, context.port);

    io_context.run();
}
catch (const std::exception& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
