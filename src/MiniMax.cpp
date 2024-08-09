#include "MiniMax.h"
#include "SuperTicTacToe.h"
#include <iostream>

unsigned long long total = 0;

void MiniMax::makeMove(SuperTicTacToe& game) {
    myCoolVariable = 0;
    auto result = bestMove(game);
    total += myCoolVariable;
    std::cout << "Move: " << (int) result.first << " Eval: " << (double)result.second << " Games Evaled: " << myCoolVariable << " total: " << total << std::endl;
    game.makeMove(result.first);
}
/*
void MiniMax::setDepth(int _depth) {
    depth = _depth;
}*/

// best move, eval
std::pair<int8_t, double> MiniMax::bestMove(SuperTicTacToe &game) {


    int _bestMove = -1;
    double bestEval = -2;

    double a = -2, b = 2;

    game.getAllMoves(myMovePool[depth]);

    for(int i = 0; i < myMovePool[depth]->size(); i++) {
        myPool[depth] = game;
        myPool[depth].makeMove((*myMovePool[depth])[i]);

        double eval = -0.99 * negamax(myPool[depth], depth - 1, -b, -a);

        //std::cout << (int)i << " " << eval << std::endl;

        if (eval > bestEval) {
            bestEval = eval;
            _bestMove = (*myMovePool[depth])[i];
        }

        if(bestEval > a) {
            a = bestEval;
        }


        if(a >= b) {
            break;
        }
    }

    assert (_bestMove != -1 && "empty Move List");

    return std::pair(_bestMove, bestEval);
}

double MiniMax::negamax(SuperTicTacToe &game, int depth, double a, double b) {
    if(game.isFinished() || depth == 0) {
        if(game.getLastPlayer()) {
            return game.eval() * -1;
        } else {
            return game.eval();
        }
    }

    double bestValue = -2;

    game.getAllMoves(myMovePool[depth]);

    for(int i = 0; i < myMovePool[depth]->size(); i++) {
        myPool[depth] = game;
        myPool[depth].makeMove((*myMovePool[depth])[i]);
        double value = -0.99 * negamax(myPool[depth], depth - 1, -b, -a);
        if(value > bestValue) {
            bestValue = value;
        }
        if(bestValue > a) {
            a = bestValue;
        }
        if(a >= b){
            break;
        }
    }
    assert (bestValue != -2 && "empty Move List");

    return bestValue;
}

MiniMax::MiniMax() {
    for(int i = 0; i < depth + 1; i++) {
        myMovePool[i] = new std::vector<int>(81);
    }
}