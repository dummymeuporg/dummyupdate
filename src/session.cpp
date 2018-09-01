#define BOOST_LOG_DYN_LINK 1
#include "session.hpp"
#include "session/initial_state.hpp"

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

Session::Session(boost::asio::ip::tcp::socket s)
    : m_socket(std::move(s)),
      m_state(new SessionState::InitialState(*this)),
      m_index(0)
{

}

void Session::start()
{
    BOOST_LOG_TRIVIAL(debug) << "Session started.";
    _doReadHeader();
}

void Session::next()
{
    BOOST_LOG_TRIVIAL(debug) << "Next command.";
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
                m_index = 0;
                m_payload.resize(m_header);
                _doReadContent();
            }

        }
    );
}

void Session::_doReadContent()
{
    auto self(shared_from_this());
    boost::asio::async_read(
        m_socket,
        boost::asio::buffer(m_payload, m_header),
        [this, self](boost::system::error_code ec, std::size_t lenght)
        {
            if (!ec)
            {
                BOOST_LOG_TRIVIAL(debug) << "Read " << lenght << " bytes.";
                m_state->onRead(m_payload);
            }
        }
    );
}

void Session::_doWrite()
{

}

