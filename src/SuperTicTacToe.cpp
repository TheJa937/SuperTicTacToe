#include "SuperTicTacToe.h"

const uint8_t moveOrder[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

unsigned long long myCoolVariable = 0;

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
    assert (!finished && "Game Over");

    if (lastMove != -1 && !games[moveToGameMove(lastMove)].isFinished()) {
        assert (moveToGame(move) == moveToGameMove(lastMove) && "Move is not in correct Game");
    }

    TicTacToe& game = games[moveToGame(move)];

    assert (!game.isFinished() && "This Game is already over");

    lastPlayer = !lastPlayer;
    lastMove = move;

    game.makeMove(lastPlayer, moveToGameMove(move));


    if(game.isFinished()) {
        // check if all games have ended
        finished = std::all_of(games, games + 9, [](TicTacToe& game) {return game.isFinished();});

        if(game.getResult() != 0) {
            thisGame.makeMove(lastPlayer, moveToGame(move));
            checkForFinish();
        }
    }
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

void SuperTicTacToe::getAllMoves(std::vector<int> *list) {
    int targetGame = moveToGameMove(lastMove);

    list->clear();

    if (lastMove == -1 || games[targetGame].isFinished()) {
        for(auto i: moveOrder) {
            games[i].appendAllMoves(list, i * 9);
        }
    } else {
        games[targetGame].appendAllMoves(list, 9 * targetGame);
    }
}

//eval not based on current player
double SuperTicTacToe::eval() {
    myCoolVariable++;
//    return (double) result;
    if(finished) {
        return (double) result;
    }
    int8_t count = 0;
    for(TicTacToe game: games) {
        count += game.count();
    }
    
    double result = ((double)(count)) / 64;

    assert (-1 < result && result < 1 && "bad eval function");
    return result;
}