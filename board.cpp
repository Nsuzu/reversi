#include "board.h"
#include <cmath>

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
    scoreMap = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    turn = 0;
}

void Board::PutStone(int x, int y){
    if(x * (x - 7) > 0 || y * (y - 7) > 0 || scoreMap[y][x] <= 0) return;

    if(map[y][x] < 0){
        map[y][x] = turn;
        ReverseStone(x, y);
        turn = (turn + 1) % 2;
    }
}

int Board::GetTileState(int x, int y){
    if(x * (x - 7) > 0 || y * (y - 7) > 0) return -1;

    return map[y][x];
}

void Board::CalcTileScore(int x, int y){
    const double angle = std::atan(1);
    int score = 0;

    for(int i = 0; i < 8; i++){
        int tmpScore = 0, dist = 1;
        std::vector<int> dir = {(int)(1.7*std::cos(angle*(float)i)), (int)(1.7*std::sin(angle*(float)i))};

        if(GetTileState(x + dir[0] * dist, y + dir[1] * dist) + turn != 1){
            continue;
        }

        tmpScore = 1;
        dist = 2;

        int state = GetTileState(x + dir[0] * dist, y + dir[1] * dist);
        while(state >= 0){
            if(state == turn){
                score += tmpScore;
                break;
            }else{
                tmpScore++;
            }

            dist++;
            state = GetTileState(x + dir[0] * dist, y + dir[1] * dist);
        }
    }

    scoreMap[y][x] = score;
}

int Board::GetTileScore(int x, int y){
    return scoreMap[y][x];
}

void Board::ReverseStone(int x, int y){
    const double angle = std::atan(1);
    for(int i = 0; i < 8; i++){
        std::vector<int> dir = {(int)(1.7*std::cos(angle*(float)i)), (int)(1.7*std::sin(angle*(float)i))};

        int state = GetTileState(x + dir[0], y + dir[1]);
        int dist = 1;
        while(state != turn && state >= 0){    
            dist++;
            state = GetTileState(x + dist*dir[0], y + dist*dir[1]);
        }
        
        if(state == turn){
            for(int j = 0; j < dist; j++){
                map[y + dir[1]*j][x + dir[0]*j] = turn;
            }
        }
    }
    
}
