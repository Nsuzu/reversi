#include "board.h"
Board::Board(){
    map = {
            {-1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, 0, 1, -1, -1, -1},
            {-1, -1, -1, 1, 0, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1}
    };
    turn = 0;
}

void Board::PutStone(int x, int y){
    if(x * (x - 7) > 0 || y * (y - 7) > 0) return;

    if(map[x][y] < 0){
        map[x][y] = turn % 2;
        turn++;
    }
}

int Board::GetTileState(int x, int y){
    if(x * (x - 7) > 0 || y * (y - 7) > 0) return -1;

    return map[x][y];
}
