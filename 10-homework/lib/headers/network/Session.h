#pragma once

#include <memory>
#include <thread>
#include <boost/asio.hpp>

#include "../Moderator.h"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(Moderator*, tcp::socket);

    void Start();

private:
    void DoRead();

    Moderator* mod;
    tcp::socket m_socket;
    static constexpr std::size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
};