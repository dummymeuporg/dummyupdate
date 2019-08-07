#include <iostream>

#include "project_content.hpp"

#include "session.hpp"
#include "session/initial_state.hpp"

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

Session::Session(boost::asio::ip::tcp::socket s,
                 const ProjectContent& project)
    : m_socket(std::move(s)),
      m_state(nullptr),
      m_project(project),
      m_index(0)
{

    for (const auto& file: project.files())
    {
        std::cerr << "Found " << file.first << std::endl;
    }
}

void Session::start()
{
    m_state = std::make_shared<SessionState::InitialState>(*this);
    std::cerr << "Session started." << std::endl;
    _doReadHeader();
}

void Session::next()
{
    std::cerr << "Next command." << std::endl;
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
            std::cerr << "Read " << length << " bytes." << std::endl;
            if (!ec)
            {
            std::cerr << "Will read " << m_header << " more bytes."
                << std::endl;
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
    auto selfState(m_state->shared_from_this());
    boost::asio::async_read(
        m_socket,
        boost::asio::buffer(m_payload, m_header),
        [this, self, selfState](boost::system::error_code ec,
                                std::size_t lenght)
        {
            if (!ec)
            {
                std::cerr << "Read " << lenght << " bytes." << std::endl;
                m_state->onRead(m_payload);
            }
        }
    );
}

void Session::_doWrite()
{

}

Session& Session::setState(std::shared_ptr<SessionState::State> state)
{
    m_state = state;
    m_state->resume();
    return *this;
}
