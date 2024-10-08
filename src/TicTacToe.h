#include <stdint.h>
#include <assert.h>
#include <string>
#include <vector>
#include <utility>
#include "MoveList.h"

#ifndef TICTACTOE
#define TICTACTOE

class TicTacToe {
    private:
        uint32_t playedMask = 0, currMask = 0;
        int8_t delta = 0;
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
        int8_t count();
};

#endif