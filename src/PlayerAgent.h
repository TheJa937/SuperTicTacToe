#include "Agent.h"

#ifndef PLAYERAGENT
#define PLAYERAGENT

class PlayerAgent : public Agent {
    public:
        void makeMove(SuperTicTacToe &game);
};



#endif