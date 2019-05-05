#pragma once

#include <cstdint>
#include <memory>

#include <boost/asio.hpp>

// Forward reference
class Session;

namespace SessionState
{
    class State : public std::enable_shared_from_this<State>
    {
    public:
        State(std::shared_ptr<Session>);
        virtual void onRead(const std::vector<std::uint8_t>&) = 0;
        virtual void resume() = 0;

    protected:
        std::shared_ptr<Session> m_session;
    };
}
