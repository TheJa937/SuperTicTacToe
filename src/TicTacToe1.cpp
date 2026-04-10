#include "TicTacToe1.h"

/*
    Board representation in Masks
    123_456_789_147_258_369_159_357_
    
1:  10000000000010000000000010000000 --> 2148008064
2:  01000000000000001000000000000000 --> 1073774592
3:  00100000000000000000100000001000 --> 536872968
4:  00001000000001000000000000000000 --> 134479872
5:  00000100000000000100000001000100 --> 67125316
6:  00000010000000000000010000000000 --> 33555456
7:  00000000100000100000000000000010 --> 8519682
8:  00000000010000000010000000000000 --> 4202496
9:  00000000001000000000001000100000 --> 2097696

full board: 11101110111011101110111011101110

    player X = true , O = false
    


*/

const uint8_t moveOrder[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
const uint32_t moveMask[] = {2148008064, 1073774592, 536872968, 134479872, 67125316, 33555456, 8519682, 4202496, 2097696};
const uint32_t fullBoard = 4008636142;
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

void TicTacToe1::checkWin() {
    if(currMask & (currMask << 1) & (currMask << 2)) {
        finished = true;
        if(lastPlayer) {
            result = 1;
        } else {
            result = -1;
        }
    }
}

void TicTacToe1::makeMove(bool player, int move) {
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

bool TicTacToe1::isFinished(){
    return finished;
}

void TicTacToe1::appendAllMoves(std::vector<int> *moves, int offset) {
    if(finished) return;

    for(int i: moveOrder) {
        if (0 == (playedMask & moveMask[i])) {
            moves->push_back(i + offset);
        }
    }
}

std::string TicTacToe1::toString() {
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

std::string TicTacToe1::toFancyString() {
    if(finished) {
        return gameOverTokens[result + 1];
    }
    return toString();
}

bool TicTacToe1::getLastPlayer() {
    return lastPlayer;
}

int8_t TicTacToe1::getResult() {
    return result;
}


