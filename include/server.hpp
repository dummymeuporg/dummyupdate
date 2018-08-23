#pragma once

// Forward declarations
namespace boost
{
    namespace asio
    {
        class io_service;
        namespace ip {
            class acceptor;
            namespace tcp {
                class endpoint;
            }
        }
    }
}


class Server {

private:

    Server(boost::asio::io_service&,
           boost::asio::tcp::acceptor&,
           boost::asio::ip::tcp::endpoint&);

    boost::asio::io_service m_ioService;
    boost::asio::tcp::acceptor& m_acceptor;
    boost::asio::tcp::ip::endpoint& m_endpoint;
};
