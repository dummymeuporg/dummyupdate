#include "server.hpp"
#include "session/state.hpp"

Session::State::State(Server& server)
    : m_server(server)
{
}
