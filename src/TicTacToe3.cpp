#include "TicTacToe3.h"

/*
    Board representation as number

    board = sum 3^i * field_i
    for all i = 0..8
    field = 
        empty: 0
        O: 1
        X: 2


*/
const int maxBoard = 3*3*3 * 3*3*3 * 3*3*3;
int8_t eval[maxBoard] = {}; // 1 draw, 0 unfinished, -1 won by X, -2 won by O
int8_t possibleMoves[maxBoard][8] = {};
const int16_t pow3[2][9] = {{1, 3, 9, 27, 81, 243, 729, 2187, 6561}, {2, 6, 18, 54, 162, 486, 1458, 4374, 13122}};
const uint8_t moveOrder[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
const char playerTokens[] = {'O', 'X'};
const std::string gameOverTokens[] = // 0: O, 1: draw, 2: X
{
" _ \n"
"| |\n"
" - \n",
"   \n"
" . \n"
"   \n",
"\\ /\n"
" X \n"
"/ \\\n"
 };



void init() {
    std::vector<int> moves(8);

    for (int board = 0; board < maxBoard; board++) {
        TicTacToe1 temp = TicTacToe3(board).toTicTacToe1();

        if (!temp.isFinished()) {
            eval[board] = 0;
        } else if (!temp.isWon()) {
            eval[board] = 1;
        } else if (temp.getLastPlayer()) {
            eval[board] = -1;
        } else {
            eval[board] = -2;
        }

        moves.clear();
        temp.appendAllMoves(&moves, 0);
        int j;
        for (j = 0; j < moves.size() && j < 8; j++) {
            possibleMoves[board][j] = moves[j];
        }
        if (j != 8) possibleMoves[board][j] = -1;
    }
}



TicTacToe3::TicTacToe3(uint16_t _board) {
    board = _board;
}

TicTacToe3::TicTacToe3() {
    board = 0;
}

TicTacToe1 TicTacToe3::toTicTacToe1() const {
    TicTacToe1 result = TicTacToe1();
    for (int i = 0; i < 9; i++) {
        if (result.isFinished()) break;
        if (getSquare(i) == 0) continue;
        result.makeMove(getSquare(i) - 1, i);
    }
    return result;
}





 bool TicTacToe3::isWon() const {
    return eval[board] < 0;
 }


void TicTacToe3::makeMove(bool player, int move) {
    assert (!isFinished && "Game is already Over");
    assert ((0 == getSquare(move)) && "Square is already ocupied");

    board += pow3[player][move];
}

bool TicTacToe3::isFinished() const {
    return eval[board] != 0;
}

void TicTacToe3::appendAllMoves(std::vector<int> *moves, int offset) const {
    if (board == 0) {
        for (auto i: moveOrder) {
            moves->push_back(i + offset);
        }
        return;
    }


    for(int i = 0; i < 8; i++) {
        if (0 > possibleMoves[board][i]) {
            break;
        }
        moves->push_back(possibleMoves[board][i] + offset);
    }
}

// 0: emtpy, 1: O, 2: X
uint8_t TicTacToe3::getSquare(uint8_t index) const {
    return (board / pow3[0][index]) % 3;
}

std::string TicTacToe3::toString() const {
    std::string result = "";

    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++){
            int index = 3 * i + j;

            if (getSquare(index) == 1) {
                result += playerTokens[0];
            } else if (getSquare(index) == 2) {
                result += playerTokens[1];
            } else {
                result.append(".");
            }
        }
        result.append("\n");
    }

    return result;
}

std::string TicTacToe3::toFancyString() const {
    if (eval[board] == 1) {
        return gameOverTokens[1];
    } else if (eval[board] == -1) {
        return gameOverTokens[2];
    } else if (eval[board] == -2) {
        return gameOverTokens[0];
    }
    return toString();
}
