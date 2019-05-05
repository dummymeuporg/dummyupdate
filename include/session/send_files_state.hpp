#pragma once

#include <fstream>

#include "session.hpp"
#include "session/state.hpp"

namespace SessionState
{
    class SendFilesState : public State
    {
    public:
        const std::uint16_t CODE_SEND = 1;
        const std::uint16_t CODE_BYE = 2;

        SendFilesState(std::shared_ptr<Session>);
        virtual void onRead(const std::vector<std::uint8_t>&) override;
        virtual void resume() override;
    private:
        static const int CHUNK_SIZE = 512;
        std::unique_ptr<std::fstream> m_currentFile;
        std::array<std::uint8_t, CHUNK_SIZE> m_chunk;

        void _sendFileHeader();
        void _sendNextFileChunk();
    };
}
