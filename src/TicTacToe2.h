#include <stdint.h>
#include <assert.h>
#include <string>
#include <vector>
#include <utility>
#include "MoveList.h"

#ifndef TICTACTOE2
#define TICTACTOE2

class TicTacToe2 {
    private:
        uint16_t playedMask = 0, currMask = 0;
        int8_t result = 0;
        bool finished = false;
        bool lastPlayer = false;

        void checkWin();

    public:
        void makeMove(bool player, int move);
        bool isFinished();
        std::string toString();
        bool getLastPlayer();
        int8_t getResult();
        std::string toFancyString();
        void appendAllMoves(std::vector<int> *moves, int offset);
};

#endif