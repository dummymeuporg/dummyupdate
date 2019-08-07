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
        virtual void resume() override;
    private:
        void _doSendFilesCount();
        void _doSendFilesCountHeader();
        void _sendNextFileInfo();

        std::map<std::string, std::array<uint32_t, 5>>::const_iterator
            m_filesIterator;
    };
}
