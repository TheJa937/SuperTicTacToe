#include "MoveList.h"


void MoveList::addMove(int move) {
    list[length] = move;
    length++;
}

void MoveList::reset() {
    length = 0;
}

int8_t MoveList::get(int i) {
    return list[i];
}

int8_t MoveList::getLength() {
    return length;
}