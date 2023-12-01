#pragma once

#include <boost/asio.hpp>
#include <mutex>

using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_service&, std::size_t);

private:
    void DoAccept();

    tcp::acceptor acceptor;
};
