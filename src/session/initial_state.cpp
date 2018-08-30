#include "session/initial_state.hpp"

SessionState::InitialState::InitialState(Session& session)
    : SessionState::State(session)
{

}

void SessionState::InitialState::onRead()
{
}
