#include "server.hpp"
#include "session.hpp"
#include "session/state.hpp"

SessionState::State::State(std::shared_ptr<Session> session)
    : m_session(session)
{
}
