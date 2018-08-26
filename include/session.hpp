#pragma once

#include <memory>

#include <boost/asio.hpp>


class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket);
    void start();

private:
    void _doRead();
    void _doWrite();

    boost::asio::ip::tcp::socket m_socket;
};
