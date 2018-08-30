#pragma once

#include "state.hpp"

namespace Session
{
    class InitialState : public State
    {
        virtual void onRead() override;
    };
}
