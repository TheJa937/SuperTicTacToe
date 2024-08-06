#include "TicTacToe.h"
#include <vector>
#include <sstream>
#include "MoveList.h"

#ifndef SUPERTICTACTOE
#define SUPERTICTACTOE

class SuperTicTacToe {
    private:
        TicTacToe games[9];

        TicTacToe thisGame;

        int8_t result = 0;
        int8_t lastMove = -1;

        bool finished = false;
        bool lastPlayer = false;



        void checkForFinish();

    public:
        void makeMove(int move);
        int8_t getResult();
        bool isFinished();
        bool getLastPlayer();
        std::string toString();
        void getAllMoves(MoveList &list);
        double eval();
};



#endif