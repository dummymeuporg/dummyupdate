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
        State(Session&);
        virtual void onRead(const std::vector<std::uint8_t>&) = 0;

    protected:
        Session& m_session;
    };
}
