#include <stdint.h>
#include <assert.h>
#include <string>
#include <vector>
#include <utility>
#include "MoveList.h"

#ifndef TICTACTOE2
#define TICTACTOE2

class TicTacToe2
{
private:
    uint16_t _playedMask = 0, currMask = 0;

    uint16_t playedMask() const;
    int8_t result() const;
    bool finished() const;
    bool lastPlayer() const;
    void flipLastPlayer();

    void handleWin();
    bool checkWin(const uint16_t mask) const;

public:
    bool getLastPlayer() const;
    void makeMove(bool player, int move);
    bool isFinished() const;
    std::string toString() const;
    std::string toFancyString() const;
    void appendAllMoves(std::vector<int> *moves, int offset) const;
    bool isWon() const;
};

#endif