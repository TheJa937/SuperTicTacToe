#include "SuperTicTacToe.h"

const uint8_t moveOrder[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};


int moveToGame(int move) {
    return move / 9;
}
int moveToGameMove(int move) {
    return move % 9;
}

void SuperTicTacToe::checkForFinish() {
    result = thisGame.getResult();
    finished |= thisGame.isFinished();
}

void SuperTicTacToe::makeMove(int move) {
    assert (move >= 0 && move < 81 && "illegal move");



    if (lastMove != -1 && !games[moveToGameMove(lastMove)].isFinished()) {
        assert (moveToGame(move) == moveToGameMove(lastMove) && "Move is not in correct Game");
    }

    TicTacToe* game = &games[moveToGame(move)];

    assert (!game->isFinished() && "This Game is already over");

    lastPlayer = !lastPlayer;
    lastMove = move;

    game->makeMove(lastPlayer, moveToGameMove(move));

    if(game->isFinished()) {
        if(game->getResult() != 0) {
            thisGame.makeMove(lastPlayer, moveToGame(move));
        }
        bool allFinished = true;
        for(TicTacToe game: games) {
            allFinished &= game.isFinished();
        }
        if(allFinished) {
            finished = true;
        }
    }

    

    checkForFinish();

}

int8_t SuperTicTacToe::getResult() {
    return result;
}

bool SuperTicTacToe::isFinished() {
    return finished;
}

bool SuperTicTacToe::getLastPlayer() {
    return lastPlayer;
}

std::string SuperTicTacToe::toString() {
    std::string result = "";

    for(int i = 0; i < 3; i++) {
        std::vector<std::string> rows;


        for(int j = 0; j < 3; j++) {
            std::string gameString = games[i*3 + j].toFancyString();
            std::stringstream ss(gameString);
            std::string line;
            while(getline(ss, line, '\n')) {
                rows.push_back(line);
            }
        }

        result += rows[0] + " | " + rows[3] + " | " + rows[6] + "\n" +
                  rows[1] + " | " + rows[4] + " | " + rows[7] + "\n" +
                  rows[2] + " | " + rows[5] + " | " + rows[8] + "\n";
        result += "    |     |     \n";
        result += "----+-----+-----\n";
        result += "    |     |     \n";
    }
    result = result.substr(0, result.length() - 17*3);

    return result;
}

std::vector<int8_t> SuperTicTacToe::getAllMoves() {
    int targetGame = moveToGameMove(lastMove);
    std::vector<int8_t> result;
    if (lastMove == -1 || games[targetGame].isFinished()) {
        for(auto i: moveOrder) {
            games[i].appendAllMoves(result, i * 9);
        }
    } else {
        games[targetGame].appendAllMoves(result, 9 * targetGame);
    }
    return result;
}

//eval not based on current player
double SuperTicTacToe::eval() {
    if(finished) {
        return (double) result;
    }
    int p1 = 0, p2 = 0;
    for(TicTacToe game: games) {
        if(game.isFinished()) {
            if(game.getResult() == 1) {
                p1 += 5;
            } else {
                p2 += 5;
            }
            continue;
        }
        auto count = game.count();
        p1 += count.first;
        p2 += count.second;
    }
    
    double result = ((double)(p1 - p2)) / 64;

    assert (-1 < result && result < 1 && "bad eval function");
    return result;
}