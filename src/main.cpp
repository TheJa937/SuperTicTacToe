#include <iostream>
#include "SuperTicTacToe.h"
#include "Agent.h"
#include "PlayerAgent.h"
#include "MiniMax.h"
#include <locale>
#include <chrono>
#include "TicTacToe3.h"
using namespace std;

struct comma_separator : std::numpunct<char> {
    char do_thousands_sep() const override { return ' '; }
    std::string do_grouping() const override { return "\3"; } // groups of 3
};

int main() {
    std::cout.imbue(std::locale(std::locale(std::cout.getloc(), new comma_separator)));

    auto start = std::chrono::high_resolution_clock::now();

    init();

    // Record end time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Init time: " << duration.count() << " ms" << std::endl;

    SuperTicTacToe game;

    Agent* agents[] = {new MiniMax(), new MiniMax()};


    int i = 0;

    while(!game.isFinished()) {
        
       agents[i % 2]->makeMove(game);

        i++;
        cout << game.toString() << endl;
    }

    for(auto a : agents) {
        delete a;
    }
    cout << "game ended with result: " << (int)game.getResult() * ((i%2) ? -1 : 1)<< endl;
}