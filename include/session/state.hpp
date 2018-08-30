#pragma once


// Forward reference
class Server;

namespace Session
{
    class State
    {
    public:
        State(Server&);
        virtual void onRead() = 0;

    private:
        Server& m_server;
    };
}
