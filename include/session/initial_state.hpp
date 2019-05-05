#pragma once

#include "session/state.hpp"

class Server;

namespace SessionState
{
    class InitialState : public State
    {
    public:
        InitialState(std::shared_ptr<Session>);
        virtual void onRead(const std::vector<std::uint8_t>&) override;
        virtual void resume() override;

    private:
        void _sendHeader();
        void _sendResult();
        std::string m_result;
    };
}
