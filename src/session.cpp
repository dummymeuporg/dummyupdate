#include "session.hpp"

#include <boost/asio.hpp>

Session::Session(boost::asio::ip::tcp::socket s) : m_socket(std::move(s))
{

}

void Session::start()
{
    _doRead();
}

void Session::_doRead()
{

}

void Session::_doWrite()
{

}

