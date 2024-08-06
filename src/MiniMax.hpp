#include "Agent.h"
#include <utility> 

#ifndef MINIMAX
#define MINIMAX
#define _depth 10
class MiniMax : public Agent {

    private:
        int depth = _depth;
        SuperTicTacToe myPool[_depth + 1];
        std::pair<int8_t, double> bestMove(SuperTicTacToe &game);
        double negamax(SuperTicTacToe &game, int depth, double a, double b);
    public:
//        MiniMax();
        void makeMove(SuperTicTacToe &game);
//        void setDepth(int _depth);
};

#undef _depth

#endif