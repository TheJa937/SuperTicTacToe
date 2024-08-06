#include "PlayerAgent.h"
#include <iostream>
#include "MoveList.h"

void PlayerAgent::makeMove(SuperTicTacToe &game) {
    std::cout << "possible moves: ";
    MoveList temp;

    game.getAllMoves(temp);

    for(int i = 0; i < temp.getLength(); i++) {
        std::cout << temp.get(i) << " ";
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