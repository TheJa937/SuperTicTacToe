#include <iostream>
#include "SuperTicTacToe.h"
#include "Agent.h"
#include "PlayerAgent.h"
#include "MiniMax.h"
#include <chrono>
#include <locale>
using namespace std;

struct comma_separator : std::numpunct<char> {
    char do_thousands_sep() const override { return ' '; }
    std::string do_grouping() const override { return "\3"; } // groups of 3
};

int main() {
    std::cout.imbue(std::locale(std::locale(std::cout.getloc(), new comma_separator)));



    SuperTicTacToe game;

    Agent* agents[] = {new MiniMax(), new MiniMax()};


    int i = 0;

    while(!game.isFinished()) {
    // Record start time
        auto start = std::chrono::high_resolution_clock::now();

        
       agents[i % 2]->makeMove(game);

        // Record end time
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate duration
        std::chrono::duration<double, std::milli> duration = end - start;

        std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

        i++;
        cout << game.toString() << endl;
    }

    for(auto a : agents) {
        delete a;
    }
    cout << "game ended with result: " << (int)game.getResult() << endl;
}