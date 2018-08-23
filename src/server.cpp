#include <boost/asio/io_service.h>
#include <boost/asio/ip/tcp.h>

#include "server.hpp"


Server::Server(boost::asio::io_service& ioService,
               boost::asio::tcp::acceptor& acceptor,
               boost::asio::ip::tcp::endpoint& endpoint)
    : m_ioService(ioService), m_acceptor(acceptor), m_endpoint(endpoint)
{
}

