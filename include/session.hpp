#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <boost/asio.hpp>

class ProjectContent;

namespace SessionState
{
    class State;
}

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket,
            const ProjectContent&);
    void start();
    void next();

    std::uint16_t header() const {
        return m_header;
    }

    boost::asio::ip::tcp::socket& socket() {
        return m_socket;
    }

    const ProjectContent& project() const {
        return m_project;
    }

    Session& setState(std::shared_ptr<SessionState::State>);

private:
    void _doReadHeader();
    void _doReadContent();
    void _doWrite();

    boost::asio::ip::tcp::socket m_socket;
    std::shared_ptr<SessionState::State> m_state;
    const ProjectContent& m_project;

    std::uint16_t m_header;
    std::vector<std::uint8_t> m_payload;
    int m_index;
};
