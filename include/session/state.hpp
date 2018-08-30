#pragma once


// Forward reference
class Session;

namespace SessionState
{
    class State
    {
    public:
        State(Session&);
        virtual void onRead() = 0;

    private:
        Session& m_session;
    };
}
