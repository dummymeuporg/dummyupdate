#pragma once

#include "session/state.hpp"

class Server;

namespace SessionState
{
    class InitialState : public State
    {
    public:
        InitialState(Session&);
        virtual void onRead(const std::vector<std::uint8_t>&) override;

    private:
        void _sendHeader();
        void _sendResult();
        std::string m_result;
    };
}
