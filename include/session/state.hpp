#pragma once

#include <cstdint>

#include <boost/asio.hpp>

// Forward reference
class Session;

namespace SessionState
{
    class State
    {
    public:
        State(Session&);
        virtual void onRead(const std::vector<std::uint8_t>&) = 0;

    protected:
        Session& m_session;
    };
}
