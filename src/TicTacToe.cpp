#include "TicTacToe.h"

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

void TicTacToe::checkWin() {
    if(currMask & (currMask << 1) & (currMask << 2)) {
        finished = true;
        result = lastPlayer?1:-1;
    }
}

void TicTacToe::makeMove(bool player, int move) {
    assert (!finished && "Game is already Over");
    assert (0 == (bool)(playedMask & moveMask[move]) && "Square is already ocupied");

    if(player) {
        player1Count++;
    } else {
        player2Count++;
    }

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

bool TicTacToe::isFinished(){
    return finished;
}

void TicTacToe::appendAllMoves(std::vector<int8_t> &moves, int offset) {
    if(finished) return;

    for(int i: moveOrder) {
        if (0 == (bool)(playedMask & moveMask[i])) {
            moves.push_back(i + offset);
        }
    }
}

std::string TicTacToe::toString() {
    std::string result = "";

    for (int i = 0; i < 12; i++) {
        if (3 == (i % 4)) {
            result.append("\n");
            continue;
        }
        if (playedMask & (1 << (31 - i))) {
            result += playerTokens[lastPlayer == (bool)(currMask & (1 << (31 - i)))];
        } else {
            result.append(".");
        }
    }

    return result;
}

std::string TicTacToe::toFancyString() {
    if(finished) {
        return gameOverTokens[result + 1];
    }
    return toString();
}

bool TicTacToe::getLastPlayer() {
    return lastPlayer;
}

int8_t TicTacToe::getResult() {
    return result;
}

std::pair<uint8_t, uint8_t> TicTacToe::count() {
    /*
    std::pair<uint8_t, uint8_t> result = std::pair(0, 0);

    for(int i: moveOrder) {
        if (0 == (bool)(currMask & moveMask[i])) {
            result.first++;
        }
    }
    currMask ^= playedMask;
    for(int i: moveOrder) {
        if (0 == (bool)(currMask & moveMask[i])) {
            result.second++;
        }
    }
    currMask ^= playedMask;

    if(!lastPlayer) {
        std::swap(result.first, result.second);
    }
    */

    return std::pair(player1Count, player2Count);
}
