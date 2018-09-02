#pragma once

#include "session/state.hpp"

class Server;

namespace SessionState
{
    class SendHashesState : public State
    {
    public:
        SendHashesState(Session&);
        virtual void onRead(const std::vector<std::uint8_t>&) override;
    };
}
