#pragma once


#include "session.hpp"
#include "session/state.hpp"

namespace SessionState
{
    class SendFilesState : public State
    {
    public:
        const std::uint16_t CODE_SEND = 1;
        const std::uint16_t CODE_BYE = 2;

        SendFilesState(Session&);
        virtual void onRead(const std::vector<std::uint8_t>&) override;
    };
}
