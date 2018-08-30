#pragma once

#include "session/state.hpp"

class Server;

namespace SessionState
{
    class InitialState : public State
    {
    public:
        InitialState(Session&);
        virtual void onRead() override;
    };
}
