#include "server.hpp"
#include "session.hpp"
#include "session/state.hpp"

SessionState::State::State(Session& session)
    : m_session(session)
{
}
