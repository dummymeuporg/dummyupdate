#define BOOST_LOG_DYN_LINK 1
#include <cstdint>

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "session.hpp"
#include "session/send_hashes_state.hpp"

#include "session/initial_state.hpp"

SessionState::InitialState::InitialState(Session& session)
    : SessionState::State(session)
{

}

void SessionState::InitialState::_sendHeader()
{
    auto self(m_session.shared_from_this());
    std::uint16_t headerLenght = m_result.size();

    boost::asio::async_write(
        m_session.socket(),
        boost::asio::buffer(&headerLenght, sizeof(headerLenght)),
        [this, self](boost::system::error_code ec, std::size_t lenght)
        {
            if (!ec)
            {
                _sendResult();
                //m_session.setState<SessionState::SendHashesState>();
                //m_session.next();
            }
        }
    );
}

void SessionState::InitialState::_sendResult()
{
    auto self(m_session.shared_from_this());
    auto selfState(shared_from_this());
    std::uint16_t headerLenght = m_result.size();

    boost::asio::async_write(
        m_session.socket(),
        boost::asio::buffer(m_result, m_result.size()),
        [this, self, selfState](boost::system::error_code ec,
                                std::size_t lenght)
        {
            if (!ec)
            {
                m_session.setState<SessionState::SendHashesState>();
                //m_session.next();
            }
        }
    );
}

void SessionState::InitialState::onRead(
    const std::vector<std::uint8_t>& buffer)
{
    BOOST_LOG_TRIVIAL(debug) << "Initial state on read";
    auto self(m_session.shared_from_this());
    std::uint16_t version = *reinterpret_cast<const std::uint16_t*>(
        buffer.data());
    BOOST_LOG_TRIVIAL(debug) << version;

    if (version == 1)
    {
        m_result = "OK";
    }
    else
    {
        m_result = "KO";
    }
    _sendHeader();
}
