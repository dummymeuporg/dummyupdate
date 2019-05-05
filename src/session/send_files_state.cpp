#define BOOST_LOG_DYN_LINK 1

#include <fstream>

#include <boost/log/trivial.hpp>

#include "project_content.hpp"
#include "session/send_files_state.hpp"


SessionState::SendFilesState::SendFilesState(std::shared_ptr<Session> session)
    : SessionState::State(session), m_currentFile(nullptr)
{

}

void SessionState::SendFilesState::resume() {

}

void SessionState::SendFilesState::onRead(
    const std::vector<std::uint8_t>& buffer)
{
    std::uint16_t command = *reinterpret_cast<const std::uint16_t*>(
        buffer.data());
    std::string filename(
        reinterpret_cast<const char*>(buffer.data()) + 2,
        size_t(buffer.size() - 2)
    );


    BOOST_LOG_TRIVIAL(debug) << "Command: " << command;
    BOOST_LOG_TRIVIAL(debug) << "Request " << filename;

    if (filename.find("..") != std::string::npos
        || command != SessionState::SendFilesState::CODE_SEND
        || !m_session->project().hasFile(filename))
    {
        // Close connexion.
    }
    else
    {
        // Check if file exist
        std::string fullpath(
            (m_session->project().projectPath() / filename).string());
        BOOST_LOG_TRIVIAL(debug) << "Fullpath: " << fullpath;
        m_currentFile = std::make_unique<std::fstream>(fullpath);
        if (m_currentFile->good())
        {
            _sendFileHeader();
        }
    }    
}


void SessionState::SendFilesState::_sendFileHeader()
{
    auto self(m_session->shared_from_this());
    auto selfState(shared_from_this());

    m_currentFile->seekg(0, std::ios::end);

    std::uint32_t fileSize = m_currentFile->tellg();
    BOOST_LOG_TRIVIAL(debug) << "File size: " << fileSize; 
    std::uint16_t code = SessionState::SendFilesState::CODE_SEND;
    std::uint16_t headerLenght = sizeof(code) + sizeof(fileSize);

    std::vector<std::uint8_t> buf;
    const std::uint8_t* pt = reinterpret_cast<const std::uint8_t*>(
        &headerLenght
    );

    // First chunk
    buf.insert(buf.begin(), pt, pt + 2);

    pt = reinterpret_cast<std::uint8_t*>(&code);

    buf.insert(buf.begin() + sizeof(headerLenght), pt, pt + 2);

    pt = reinterpret_cast<std::uint8_t*>(&fileSize);

    // Next chunk
    buf.insert(buf.begin() + sizeof(headerLenght) + sizeof(code),
               pt, pt + 4);

    boost::asio::async_write(
        m_session->socket(),
        boost::asio::buffer(buf),
        [this,
         self,
         selfState](boost::system::error_code ec, std::size_t lenght)
        {
            if (!ec)
            {
                m_currentFile->clear();
                m_currentFile->seekg(0);
                _sendNextFileChunk();
            }
        }
    );
}


void SessionState::SendFilesState::_sendNextFileChunk()
{
    auto self(m_session->shared_from_this());
    auto selfState(shared_from_this());
    m_currentFile->read(reinterpret_cast<char*>(m_chunk.data() + 2),
                        m_chunk.size() - 2);
    std::streamsize n = m_currentFile->gcount();
    BOOST_LOG_TRIVIAL(debug) << "Chunk: " << n;
    std::copy_n(reinterpret_cast<char*>(&n), 2, m_chunk.data());
    BOOST_LOG_TRIVIAL(debug) << "offset: " << m_currentFile->tellg();

    if (n == 0)
    {
       m_session->next();
    }
    else
    {
        boost::asio::async_write(
            m_session->socket(),
            boost::asio::buffer(m_chunk, n + 2),
            [this,
             self,
             selfState](boost::system::error_code ec, std::size_t lenght)
            {
                if (!ec)
                {
                    _sendNextFileChunk();
                }
            }
        );
    }
}
