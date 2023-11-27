#pragma once

#include <memory>
#include <boost/asio.hpp>

#include "Session.h"
#include "../Moderator.h"

using boost::asio::ip::tcp;

class Server
{
public:
    Server(boost::asio::io_service&, std::size_t, std::size_t);

private:
    void DoAccept();

    tcp::acceptor acceptor;
    Moderator* mod;
};