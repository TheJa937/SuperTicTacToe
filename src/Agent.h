#include "SuperTicTacToe.h"

#ifndef AGENT
#define AGENT

class Agent {
    public:
        virtual void makeMove(SuperTicTacToe &game) = 0;
};



#endif