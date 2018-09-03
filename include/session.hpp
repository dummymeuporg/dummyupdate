#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <boost/asio.hpp>

namespace Dummy
{
    class Project;
}

namespace SessionState
{
    class State;
}

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket,
            const Dummy::Project&);
    void start();
    void next();

    std::uint16_t header() const {
        return m_header;
    }

    boost::asio::ip::tcp::socket& socket() {
        return m_socket;
    }

    const Dummy::Project& project() const {
        return m_project;
    }

    template<typename T>
    Session& setState()
    {
        m_state = std::make_unique<T>(*this);
        return *this;
    }

private:
    void _doReadHeader();
    void _doReadContent();
    void _doWrite();

    boost::asio::ip::tcp::socket m_socket;
    std::unique_ptr<SessionState::State> m_state;
    const Dummy::Project& m_project;

    std::uint16_t m_header;
    std::vector<std::uint8_t> m_payload;
    int m_index;
};
