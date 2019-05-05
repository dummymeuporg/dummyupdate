#include <iostream>

#include <boost/log/trivial.hpp>

#include "project_content.hpp"
#include "session.hpp"

#include "session/send_files_state.hpp"
#include "session/send_hashes_state.hpp"

SessionState::SendHashesState::SendHashesState(
    std::shared_ptr<Session> session
) : SessionState::State(session)
{
}

void SessionState::SendHashesState::resume()
{
    _doSendFilesCountHeader();
}

void SessionState::SendHashesState::onRead(
    const std::vector<std::uint8_t>& buffer)
{
}

void SessionState::SendHashesState::_doSendFilesCountHeader()
{
    auto self(m_session->shared_from_this());
    std::uint16_t countHeader = sizeof(std::uint32_t);
    boost::asio::async_write(
        m_session->socket(),
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

    auto self(m_session->shared_from_this());
    auto selfState(shared_from_this());
    std::uint32_t filesCount = m_session->project().files().size();
    std::cerr << "Count: " << filesCount << std::endl;
    boost::asio::async_write(
        m_session->socket(),
        boost::asio::buffer(&filesCount, sizeof(filesCount)),
        [this,
         self,
         selfState](boost::system::error_code ec, std::size_t lenght)
        {
            if (!ec)
            {
                for(auto it = m_session->project().files().begin();
                        it != m_session->project().files().end(); ++it) {
                    std::cerr << "Test: " << it->first << std::endl;
                }
                m_filesIterator = m_session->project().files().begin();
                std::cerr << "Iteration: " << m_filesIterator->first
                    << std::endl;
                //m_session.next();
                _sendNextFileInfo();
            }
        }
    );
}

void SessionState::SendHashesState::_sendNextFileInfo()
{
    auto self(m_session->shared_from_this());
    const std::string& filename(m_filesIterator->first);
    const std::array<unsigned int, 5> hash(m_filesIterator->second);
    std::uint16_t bufSize = filename.size() +
        hash.size() * sizeof(std::uint32_t);

    const std::uint8_t* pt = reinterpret_cast<const std::uint8_t*>(&bufSize);
    std::vector<uint8_t> buf;

    // Set packet size
    buf.insert(buf.begin(), pt, pt + 2);

    // Insert filename
    buf.insert(buf.begin() + 2, filename.begin(), filename.end());

    // Insert hash
    pt = reinterpret_cast<const std::uint8_t*>(hash.data());
    buf.insert(
        buf.begin() + 2 + filename.size(),
        pt,
        pt + sizeof(std::uint32_t) * hash.size()
    );

    boost::asio::async_write(
        m_session->socket(),
        boost::asio::buffer(buf),
        [this, self](boost::system::error_code ec, std::size_t lenght)
        {
            if (!ec)
            {
                std::cerr << "Switch to next iteration" << std::endl;
                ++m_filesIterator;
                std::cerr << "Iteration: " << m_filesIterator->first << std::endl;

                if (m_filesIterator == m_session->project().files().end())
                {
                    std::cerr << "Change state." << std::endl;
                    m_session->setState(
                        std::make_shared<SessionState::SendFilesState>(
                            m_session->shared_from_this()
                        )
                    );
                    m_session->next();
                }
                else
                {
                    std::cerr << "Next file." << std::endl;
                    _sendNextFileInfo();                
                }
            }
        }
    );
}
