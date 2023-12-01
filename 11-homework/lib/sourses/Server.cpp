#include "../headers/network/Server.h"
#include "../headers/network/Session.h"

Server::Server(boost::asio::io_service& io_context, std::size_t port) : acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
    DoAccept();
}

void Server::DoAccept()
{
    acceptor.async_accept(
    [this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
            std::make_shared<Session>(std::move(socket))->Start();

        DoAccept();
    });
}
