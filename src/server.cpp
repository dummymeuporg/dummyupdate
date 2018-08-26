#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "server.hpp"


Server::Server(boost::asio::io_service& ioService, unsigned short port)
    : m_acceptor(ioService,
                 boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                port))
{
    _doAccept();
}

void Server::_doAccept()
{
}
