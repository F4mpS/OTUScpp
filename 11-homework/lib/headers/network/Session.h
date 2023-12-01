#pragma once

#include <boost/asio.hpp>
#include <memory>

#include "../Command.h"
#include "../ThreadPool.h"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket);
    void Start();

private:
    void DoRead();
    void DoWrite(const std::string&);

    tcp::socket socket;
    static constexpr std::size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    std::string tempStr;
};
