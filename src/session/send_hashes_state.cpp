#define BOOST_LOG_DYN_LINK 1

#include "dummy/project.hpp"
#include "session.hpp"
#include "session/send_hashes_state.hpp"

SessionState::SendHashesState::SendHashesState(Session& session)
    : SessionState::State(session)
{
    _doSendFilesCountHeader();
}

void SessionState::SendHashesState::onRead(
    const std::vector<std::uint8_t>& buffer)
{
    auto self(m_session.shared_from_this());
}

void SessionState::SendHashesState::_doSendFilesCountHeader()
{
    auto self(m_session.shared_from_this());
    std::uint16_t countHeader = sizeof(std::uint32_t);
    boost::asio::async_write(
        m_session.socket(),
        boost::asio::buffer(&countHeader, sizeof(countHeader)),
        [this, self](boost::system::error_code ec, std::size_t lenght)
        {
            if (!ec)
            {
                _doSendFilesCount();
            }
        }
    );
}

void SessionState::SendHashesState::_doSendFilesCount()
{

    auto self(m_session.shared_from_this());
    std::uint32_t filesCount = m_session.project().files().size();
    boost::asio::async_write(
        m_session.socket(),
        boost::asio::buffer(&filesCount, sizeof(filesCount)),
        [this, self](boost::system::error_code ec, std::size_t lenght)
        {
            if (!ec)
            {
                m_filesIterator = m_session.project().files().begin();
                m_session.next();
            }
        }
    );
}

void SessionState::SendHashesState::_sendNextFileInfo()
{
}
