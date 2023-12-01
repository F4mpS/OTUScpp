#include <iostream>

#include "../headers/network/Session.h"

Session::Session(tcp::socket socket) : socket(std::move(socket)) {}

void Session::Start()
{
    DoRead();
}

void Session::DoRead()
{
    auto self(shared_from_this());

    socket.async_read_some(boost::asio::buffer(buffer, BUFFER_SIZE),
    [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (ec)
            return -1;

        std::string str(buffer, length);
        std::size_t pos = str.rfind('\n');

        if (pos == std::string::npos)
        {
            tempStr += str;
            DoRead();
            return -1;
        }

        auto input = std::make_shared<std::istringstream>(tempStr + str.substr(0, pos));
        tempStr = std::string(str.data() + pos + 1, str.size() - pos - 1);

        auto job = [this, input, self]()
        {
            std::string line;
            std::string res;
            while (std::getline(*input, line))
                res += SendCommand(line) + "\n";

            DoWrite(res);
        };

        ThreadPool::get_instance()->enqueue(job);
    });
}

void Session::DoWrite(const std::string& str)
{
    auto self(shared_from_this());

    boost::asio::async_write(socket, boost::asio::buffer(str.c_str(), str.size()),
    [this, self](boost::system::error_code ec, std::size_t)
    {
        if (!ec)
        {
            DoRead();
        }
    });
}
