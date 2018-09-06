#include "session/send_files_state.hpp"


SessionState::SendFilesState::SendFilesState(Session& session)
    : SessionState::State(session)
{

}

void SessionState::SendFilesState::onRead(
    const std::vector<std::uint8_t>& buffer)
{
    auto self(m_session.shared_from_this());
    
}



