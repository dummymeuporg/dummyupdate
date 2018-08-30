#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "session/initial_state.hpp"
#include "server.hpp"
#include "session.hpp"


Server::Server(boost::asio::io_service& ioService, unsigned short port)
    : m_acceptor(ioService,
                 boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                                port))
{
    _doAccept();
}

void Server::_doAccept()
{
    m_acceptor.async_accept(
        [this](boost::system::error_code ec,
               boost::asio::ip::tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<Session>(std::move(socket))->start();
            }
            _doAccept();
        }
    );
}
