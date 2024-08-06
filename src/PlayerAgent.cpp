#include "PlayerAgent.h"
#include <iostream>

void PlayerAgent::makeMove(SuperTicTacToe &game) {
    std::cout << "possible moves: ";
    for(int i:game.getAllMoves()) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    int a, b;
    std::cout << "board: ";
    std::cin >> a;
    std::cout << "square: ";
    std::cin >> b;
    a--;
    b--;

    game.makeMove(a * 9 + b);

}