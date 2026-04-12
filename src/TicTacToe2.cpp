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

    last player is stored as top bit of played board


*/

const uint8_t moveOrder[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
const uint16_t moveMask[] = {1024, 512, 256, 64, 32, 16, 4, 2, 1};
const uint16_t fullBoard = 1911;
const uint16_t lastPlayerMask = 1 << 15;
const char playerTokens[] = {'O', 'X'};
const std::string gameOverTokens[] =
    {
        " _ \n"
        "| |\n"
        " - \n",
        "   \n"
        " . \n"
        "   \n",
        "\\ /\n"
        " X \n"
        "/ \\\n"};

// 1: game was won by last player      0: draw
int8_t TicTacToe2::result() const
{
    return isWon();
}

bool TicTacToe2::finished() const
{
    return playedMask() == fullBoard;
}

uint16_t TicTacToe2::playedMask() const
{
    return (lastPlayerMask - 1) & _playedMask;
}

bool TicTacToe2::lastPlayer() const
{
    return _playedMask & lastPlayerMask;
}

void TicTacToe2::flipLastPlayer()
{
    currMask ^= playedMask();
    _playedMask ^= lastPlayerMask;
}

bool TicTacToe2::checkWin(const uint16_t mask) const
{
    return mask & (mask >> 1) & (mask >> 2) ||
           mask & (mask >> 4) & (mask >> 8) ||
           mask & (mask >> 5) & (mask >> 10) ||
           mask & (mask >> 3) & (mask >> 6);
}

bool TicTacToe2::isWon() const
{
    return currMask == fullBoard;
}

void TicTacToe2::handleWin()
{
    if (checkWin(currMask))
    {
        _playedMask |= fullBoard;
        currMask = fullBoard;
    }
}

void TicTacToe2::makeMove(bool player, int move)
{
    assert(!finished() && "Game is already Over");
    assert(0 == (bool)(playedMask() & moveMask[move]) && "Square is already ocupied");

    if (lastPlayer() != player)
    {
        flipLastPlayer();
    }

    currMask |= moveMask[move];
    _playedMask |= moveMask[move];

    handleWin();
}

bool TicTacToe2::isFinished() const
{
    return finished();
}

void TicTacToe2::appendAllMoves(std::vector<int> *moves, int offset) const
{
    if (finished())
        return;

    for (int i : moveOrder)
    {
        if (0 == (playedMask() & moveMask[i]))
        {
            moves->push_back(i + offset);
        }
    }
}

std::string TicTacToe2::toString() const
{
    std::string result = "";

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int index = 3 * i + j;

            if (playedMask() & moveMask[index])
            {
                result += playerTokens[lastPlayer() == (bool)(currMask & moveMask[index])];
            }
            else
            {
                result.append(".");
            }
        }
        result.append("\n");
    }

    return result;
}

std::string TicTacToe2::toFancyString() const
{
    if (isFinished())
    {
        if (isWon())
        {
            return gameOverTokens[lastPlayer() ? 2 : 0];
        }
        else
        {
            return gameOverTokens[1];
        }
    }
    return toString();
}

bool TicTacToe2::getLastPlayer() const
{
    return lastPlayer();
}
