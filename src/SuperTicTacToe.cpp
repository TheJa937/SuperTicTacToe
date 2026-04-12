#include "SuperTicTacToe.h"

const uint8_t moveOrder[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
const uint8_t boardValue[] = {2, 1, 2, 1, 3, 1, 2, 1, 2};
unsigned long long exploredNodes = 0;

int moveToGame(int move)
{
    return move / 9;
}
int moveToGameMove(int move)
{
    return move % 9;
}

void SuperTicTacToe::makeMove(int move)
{
    assert(move >= 0 && move < 81 && "illegal move");
    assert(!isFinished() && "Game Over");

    int gameIndex = moveToGame(move);

    if (lastMove != -1 && !games[moveToGameMove(lastMove)].isFinished())
    {
        assert(gameIndex == moveToGameMove(lastMove) && "Move is not in correct Game");
    }

    TicTacToe &game = games[gameIndex];

    assert(!game.isFinished() && "This Game is already over");

    lastPlayer = !lastPlayer;
    lastMove = move;

    game.makeMove(lastPlayer, moveToGameMove(move));

    /*
    int _delta;
    if (player) {
        _delta = 1;
    } else {
        _delta = -1;
    }
    if (game.isFinished()) {
        _delta = game.getResult() * 5;
    }
    _delta *= boardValue[gameIndex];
    if (game.isFinished()) {
        // in this case the returned delta is absolute
        _delta -= delta[gameIndex];
        //delta[gameIndex] += _delta; //doesnt matter anymore - delta is not needed later
    } else {
        // in this case the returned delta is relative
        delta[gameIndex] += _delta;
    }

    delta[9] += _delta;
    */

    if (game.isWon())
    {
        delta += boardValue[moveToGame(move)] * (lastPlayer ? 1 : -1);
        thisGame.makeMove(lastPlayer, moveToGame(move));
    }
    if (game.isFinished())
    {
        // check if all games have ended
        finished = thisGame.isFinished() || std::all_of(games, games + 9, [](const TicTacToe &game)
                                                        { return game.isFinished(); });
    }
}

// 1: game was won by last player  0: draw
int8_t SuperTicTacToe::getResult() const
{
    return thisGame.isWon();
}

bool SuperTicTacToe::isFinished() const
{
    return finished;
}

bool SuperTicTacToe::getLastPlayer() const
{
    return lastPlayer;
}

std::string SuperTicTacToe::toString() const
{
    std::string result = "";
    result += "    |     |     \n";
    for (int i = 0; i < 3; i++)
    {
        std::vector<std::string> rows;

        for (int j = 0; j < 3; j++)
        {
            std::string gameString = games[i * 3 + j].toFancyString();
            std::stringstream ss(gameString);
            std::string line;
            while (getline(ss, line, '\n'))
            {
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
    result = result.substr(0, result.length() - 17 * 3);
    result += "    |     |     \n";
    return result;
}

void SuperTicTacToe::getAllMoves(std::vector<int> *list) const
{
    int targetGame = moveToGameMove(lastMove);

    list->clear();

    if (lastMove == -1 || games[targetGame].isFinished())
    {
        for (auto i : moveOrder)
        {
            games[i].appendAllMoves(list, i * 9);
        }
    }
    else
    {
        games[targetGame].appendAllMoves(list, 9 * targetGame);
    }
}

// eval based on last played player
double SuperTicTacToe::eval() const
{
    exploredNodes++;
    if (!isFinished())
    {
        double result = (getLastPlayer() ? 1 : -1) * (double)delta / 16;
        assert(-1 < result && result < 1 && "bad eval function");
        return result;
    }

    return (double)getResult();
}