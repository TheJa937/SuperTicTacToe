#include <iostream>
#include "SuperTicTacToe.h"
#include "Agent.h"
#include "PlayerAgent.h"
#include "MiniMax.hpp"

using namespace std;

int main() {
    SuperTicTacToe game;

    Agent* agents[] = {new MiniMax(), new MiniMax()};


    int i = 0;

    while(!game.isFinished()) {
       agents[i % 2]->makeMove(game);
        i++;
        cout << game.toString() << endl;
    }


    cout << "game ended with result: " << (int)game.getResult() << endl;
}