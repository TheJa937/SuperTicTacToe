#include <stdint.h>
#include <assert.h>
#include <string>
#include <vector>
#include <array>
#include "TicTacToe1.h"

#ifndef TICTACTOE3
#define TICTACTOE3

void init();

class TicTacToe3 {
    private:
        uint16_t board = 0;


        uint8_t getSquare(uint8_t index) const;


    public:
        TicTacToe1 toTicTacToe1() const;
        TicTacToe3();
        TicTacToe3(uint16_t _board);
        void makeMove(bool player, int move);
        bool isFinished() const;
        std::string toString() const;
        std::string toFancyString() const;
        void appendAllMoves(std::vector<int> *moves, int offset) const;
        bool isWon() const;
};



#endif