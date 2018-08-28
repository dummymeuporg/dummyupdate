#define BOOST_LOG_DYN_LINK 1
#include "session.hpp"

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

Session::Session(boost::asio::ip::tcp::socket s) : m_socket(std::move(s))
{

}

void Session::start()
{
    BOOST_LOG_TRIVIAL(debug) << "Session started.";
    _doReadHeader();
}

void Session::_doReadHeader()
{
    auto self(shared_from_this());
    boost::asio::async_read(
        m_socket,
        boost::asio::buffer(&m_header, sizeof(std::uint16_t)),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            BOOST_LOG_TRIVIAL(debug) << "Read " << length << " bytes.";
            if (!ec)
            {
                BOOST_LOG_TRIVIAL(debug) << "Will read "
                                         << m_header << " more bytes.";
            }

            _doReadContent();
        }
    );
}

void Session::_doReadContent()
{

}

void Session::_doWrite()
{

}

