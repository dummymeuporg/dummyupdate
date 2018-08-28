#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

class Server {

public:
    const int ACTUAL_VERSION = 1;
    Server(boost::asio::io_service&, unsigned short);

private:
    void _doAccept();

    boost::asio::ip::tcp::acceptor m_acceptor;
};
