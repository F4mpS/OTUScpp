#include "../headers/network/Server.h"

Server::Server(boost::asio::io_service& ioService, std::size_t port, std::size_t bulkSize) : acceptor(ioService, tcp::endpoint(tcp::v4(), port)), mod(new Moderator(bulkSize))
{	
	DoAccept();
}

void Server::DoAccept()
{	
    acceptor.async_accept(
    [this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
		    std::make_shared<Session>(mod, std::move(socket))->Start();
    	        	
        DoAccept();
	});
}