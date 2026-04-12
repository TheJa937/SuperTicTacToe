#include <stdint.h>
#include <assert.h>
#include <string>
#include <vector>
#include <utility>
#include "MoveList.h"

#ifndef TICTACTOE1
#define TICTACTOE1

class TicTacToe1
{
private:
    uint32_t playedMask = 0, currMask = 0;

    int8_t result = 0;
    bool finished = false;
    bool lastPlayer = false;

    void handleWin();
    bool checkWin(uint32_t mask) const;

public:
    void makeMove(bool player, int move);
    bool getLastPlayer() const;
    bool isFinished() const;
    std::string toString() const;
    std::string toFancyString() const;
    void appendAllMoves(std::vector<int> *moves, int offset) const;
    bool isWon() const;
};

#endif