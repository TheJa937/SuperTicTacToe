#include "TicTacToe2.h"

/*
    Board representation in Masks
    ____ _123 _456 _789 
    
1:  0000 0100 0000 0000 --> 1024
2:  0000 0010 0000 0000 --> 512
3:  0000 0001 0000 0000 --> 256
4:  0000 0000 0100 0000 --> 64
5:  0000 0000 0010 0000 --> 32
6:  0000 0000 0001 0000 --> 16
7:  0000 0000 0000 0100 --> 4
8:  0000 0000 0000 0010 --> 2
9:  0000 0000 0000 0001 --> 1

full board: 0000 0111 0111 0111

    player X = true , O = false
    


*/

const uint8_t moveOrder[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
const uint16_t moveMask[] = {1024, 512, 256, 64, 32, 16, 4, 2, 1};
const uint16_t fullBoard = 1911;
const char playerTokens[] = {'O', 'X'};
const std::string gameOverTokens[] = 
{
" _ \n"
"| |\n"
" ¯ \n",
"   \n"
" . \n"
"   \n",
"\\ /\n"
" X \n"
"/ \\\n"
 };

void TicTacToe2::checkWin() {
    if(currMask & (currMask >> 1) & (currMask >> 2) || 
       currMask & (currMask >> 4) & (currMask >> 8) ||
       currMask & (currMask >> 5) & (currMask >> 10) ||
       currMask & (currMask >> 3) & (currMask >> 6)) {
        finished = true;
        if(lastPlayer) {
            result = 1;
        } else {
            result = -1;
        }
    }
}

void TicTacToe2::makeMove(bool player, int move) {
    assert (!finished && "Game is already Over");
    assert (0 == (bool)(playedMask & moveMask[move]) && "Square is already ocupied");


    if (lastPlayer != player) {
        currMask ^= playedMask;
    }

    currMask |= moveMask[move];
    playedMask |= moveMask[move];
    lastPlayer = player;


    checkWin();

    if (playedMask == fullBoard) {
        finished = true;
    }


}

bool TicTacToe2::isFinished(){
    return finished;
}

void TicTacToe2::appendAllMoves(std::vector<int> *moves, int offset) {
    if(finished) return;

    for(int i: moveOrder) {
        if (0 == (playedMask & moveMask[i])) {
            moves->push_back(i + offset);
        }
    }
}

std::string TicTacToe2::toString() {
    std::string result = "";

    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++){
            int index = 3 * i + j;

            if (playedMask & moveMask[index]) {
                result += playerTokens[lastPlayer == (bool)(currMask & moveMask[index])];
            } else {
                result.append(".");
            }
        }
        result.append("\n");
    }

    return result;
}

std::string TicTacToe2::toFancyString() {
    if(finished) {
        return gameOverTokens[result + 1];
    }
    return toString();
}

bool TicTacToe2::getLastPlayer() {
    return lastPlayer;
}

int8_t TicTacToe2::getResult() {
    return result;
}


