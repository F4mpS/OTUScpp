#include "../headers/network/Session.h"

Session::Session(Moderator* moderator, tcp::socket socket) : mod(moderator), m_socket(std::move(socket)) {}

void Session::Start()
{
    DoRead();
}

void Session::DoRead()
{
    auto self(shared_from_this());

    m_socket.async_read_some(boost::asio::buffer(buffer, BUFFER_SIZE),
    [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (!ec)
        {
            mod->ReadBuffer(buffer, length, this);
            DoRead();
        }
    });
}