#include <vector>
#include <sstream>
#include <algorithm>
#include "TicTacToe1.h"
#include "TicTacToe2.h"
#include "MoveList.h"

#ifndef SUPERTICTACTOE
#define SUPERTICTACTOE
#define TICTACTOE TicTacToe1
extern unsigned long long myCoolVariable;

class SuperTicTacToe {
    private:
        TICTACTOE games[9];

        TICTACTOE thisGame;

        int8_t result = 0;
        int8_t lastMove = -1;

        bool finished = false;
        bool lastPlayer = false;
        int8_t delta[10] = {0}; // eval of every small board, delta[9] is a precomputed sum over all boards


        void checkForFinish();

    public:
        void makeMove(int move);
        int8_t getResult();
        bool isFinished();
        bool getLastPlayer();
        std::string toString();
        void getAllMoves(std::vector<int> *list);
        double eval();
};



#endif