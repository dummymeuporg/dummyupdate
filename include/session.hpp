#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <boost/asio.hpp>

namespace SessionState
{
    class State;
}

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket);
    void start();

    std::uint16_t header() const {
        return m_header;
    }

private:
    void _doReadHeader();
    void _doReadContent();
    void _doWrite();

    boost::asio::ip::tcp::socket m_socket;
    std::unique_ptr<SessionState::State> m_state;
    std::uint16_t m_header;
    std::vector<std::uint8_t> m_payload;
    int m_index;
};
