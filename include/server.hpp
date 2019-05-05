#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

class ProjectContent;

class Server {

public:
    const int ACTUAL_VERSION = 1;
    Server(boost::asio::io_service&, unsigned short, const ProjectContent&);

private:
    void _doAccept();

    boost::asio::ip::tcp::acceptor m_acceptor;
    const ProjectContent& m_project;
};
