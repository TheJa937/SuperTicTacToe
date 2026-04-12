#include "MiniMax.h"
#include "SuperTicTacToe.h"
#include <iostream>
#include <chrono>

unsigned long long total = 0;

void MiniMax::makeMove(SuperTicTacToe &game)
{
    exploredNodes = 0;
    // Record start time
    auto start = std::chrono::high_resolution_clock::now();

    auto result = bestMove(game);

    // Record end time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    total += exploredNodes;
    std::cout << "Move: " << (int)result.first << " Eval: " << (double)result.second << " Games Evaled: " << exploredNodes << " total: " << total << std::endl;
    std::cout << "Execution time: " << duration.count() << " ms    Speed: " << (double)exploredNodes / duration.count() << " Nodes/ms" << std::endl;
    game.makeMove(result.first);
}
/*
void MiniMax::setDepth(int _depth) {
    depth = _depth;
}*/

// best move, eval
std::pair<int8_t, double> MiniMax::bestMove(SuperTicTacToe &game)
{

    int _bestMove = -1;
    double bestEval = -2;

    double a = -2, b = 2;

    game.getAllMoves(myMovePool[depth]);

    /*
    std::cout << "Possible Moves: ";
    for (auto i : *myMovePool[depth]) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    */

    for (auto i : *myMovePool[depth])
    {
        myPool[depth] = game;
        myPool[depth].makeMove(i);

        double eval = -1 * negamax(myPool[depth], depth - 1, -b, -a);

        if (eval > bestEval)
        {
            bestEval = eval;
            _bestMove = i;
        }

        if (bestEval > a)
        {
            a = bestEval;
        }

        if (a >= b)
        {
            break;
        }
    }

    assert(_bestMove != -1 && "empty Move List");

    return std::pair(_bestMove, bestEval);
}

double MiniMax::negamax(SuperTicTacToe &game, int depth, double a, double b)
{
    if (game.isFinished() || depth == 0)
    {
        return game.eval() * -1;
    }

    double bestValue = -2;

    game.getAllMoves(myMovePool[depth]);

    for (int i = 0; i < myMovePool[depth]->size(); i++)
    {
        myPool[depth] = game;
        myPool[depth].makeMove((*myMovePool[depth])[i]);
        double value = -1 * negamax(myPool[depth], depth - 1, -b, -a);
        if (value > bestValue)
        {
            bestValue = value;
        }
        if (bestValue > a)
        {
            a = bestValue;
        }
        if (a >= b)
        {
            break;
        }
    }
    assert(bestValue != -2 && "empty Move List");

    return bestValue;
}

MiniMax::MiniMax()
{
    for (int i = 0; i < depth + 1; i++)
    {
        myMovePool[i] = new std::vector<int>(81);
    }
}
MiniMax::~MiniMax()
{
    for (int i = 0; i < depth + 1; i++)
    {
        delete myMovePool[i];
    }
}