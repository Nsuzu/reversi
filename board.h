#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board{
    private:
        std::vector<std::vector<int>> map;
        int turn;

    public:
        Board();
        void PutStone(int, int);
        int GetTileState(int, int);
};

#endif