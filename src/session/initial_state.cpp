#define BOOST_LOG_DYN_LINK 1
#include <cstdint>

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "session/initial_state.hpp"

SessionState::InitialState::InitialState(Session& session)
    : SessionState::State(session)
{

}

void SessionState::InitialState::onRead(
    const std::vector<std::uint8_t>& buffer)
{
    BOOST_LOG_TRIVIAL(debug) << "Initial state on read";
}
