#include <iostream>
#include <boost/asio.hpp>

#include "../lib/headers/network/Server.h"

int main(int argc, char* argv[])
{
    try {
        if(argc != 3) 
        {
            std::cerr << "Usage: bulk_server <port> <bulk_size>" << std::endl;
            return 1;
        }
        boost::asio::io_context io_context;
        
        Server s(io_context, atoi(argv[1]), atoi(argv[2]));
     
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    // std::string n; // future bulk size
    // std::getline(std::cin, n);
    // Moderator mod(std::stoi(n), std::cin);
    // mod.AddOutputFile("bulk");
    // mod.AddOutputFile("bulk");
    // mod.AddOutputStream(std::cout);
    // std::cin.clear();
    // mod.StartReading();

    return 0;
}
