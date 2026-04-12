#include <vector>
#include <sstream>
#include <algorithm>
#include "TicTacToe1.h"
#include "TicTacToe2.h"
#include "TicTacToe3.h"
#include "MoveList.h"

#ifndef SUPERTICTACTOE
#define SUPERTICTACTOE
#define TicTacToe TicTacToe3
extern unsigned long long exploredNodes;

class SuperTicTacToe
{
private:
    TicTacToe games[9];
    TicTacToe thisGame;

    bool lastPlayer = false;
    int8_t lastMove = -1;

    bool finished = false;
    int8_t delta = 0;
    // int8_t delta[10] = {0}; // eval of every small board, delta[9] is a precomputed sum over all boards

public:
    void makeMove(int move);
    int8_t getResult() const;
    bool isFinished() const;
    bool getLastPlayer() const;
    std::string toString() const;
    void getAllMoves(std::vector<int> *list) const;
    double eval() const;
};

#endif