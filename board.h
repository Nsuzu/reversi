#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board{
    private:
        std::vector<std::vector<int>> map;
        std::vector<std::vector<int>> scoreMap;
        int turn;

    public:
        Board();
        void PutStone(int, int);
        int GetTileState(int, int);
        void CalcTileScore(int, int);
        int GetTileScore(int, int);
        void ReverseStone(int, int);
};

#endif