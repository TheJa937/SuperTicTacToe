#include <stdint.h>

#ifndef MOVELIST
#define MOVELIST

class MoveList {
    private:
        int8_t list[81] = {};
        int8_t length = 0;
    public:
        void addMove(int move);
        void reset();
        int8_t get(int i);
        int8_t getLength();
};



#endif