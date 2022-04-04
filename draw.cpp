#include <windows.h>
#include <gdiplus.h>
#include "draw.h"
using namespace Gdiplus;

const int boardSize = 480, space = boardSize / 8;
const int wndWidth = 1120, wndHeight = 630;

const int ori[] = {(wndWidth - boardSize)/2, (wndHeight - boardSize)/2};
int baseDrawn = 0;

void DrawBase(HDC hdc){
    Gdiplus::Graphics graphics(hdc);
    Gdiplus::SolidBrush baseGreen(Gdiplus::Color(255, 0, 100, 0));
    if(baseDrawn == 0){
        graphics.FillRectangle(&baseGreen, ori[0], ori[1], boardSize, boardSize);
        baseDrawn = 1;
    }
    

    Gdiplus::Pen linePen0(Gdiplus::Color(255, 0, 0, 0), 2);
    for(int i = 0; i < 9; i++){
        graphics.DrawLine(&linePen0, ori[0] + space*i, ori[1], ori[0] + space*i, ori[1] + boardSize);
    }
    for(int i = 0; i < 9; i++){
        graphics.DrawLine(&linePen0, ori[0], ori[1] + space*i, ori[0] + boardSize, ori[1] + space*i);
    }
}

void DrawStone(HDC hdc, int x, int y, int state){
    const int stoneSpace = 5;
    Gdiplus::Graphics graphics(hdc);
    Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 255*state, 255*state, 255*state));
    Gdiplus::SolidBrush baseGreen(Gdiplus::Color(255, 0, 100, 0));
    if(state < 0){
        graphics.FillEllipse(
            &baseGreen,
            ori[0] + space*x + stoneSpace, ori[1] + space*y + stoneSpace,
            space - stoneSpace * 2, space - stoneSpace * 2
        );
        return;
    }
    

    graphics.FillEllipse(
        &whiteBrush,
        ori[0] + space*x + stoneSpace, ori[1] + space*y + stoneSpace,
        space - stoneSpace * 2, space - stoneSpace * 2
    );
}

void SuggestPos(HDC hdc, int x, int y, int score){
    if(score <= 0) return;
    const int stoneSpace = 5;
    Gdiplus::Graphics graphics(hdc);
    Gdiplus::SolidBrush suggestBrush(Gdiplus::Color(100, 100, 0, 0));

    graphics.FillEllipse(
        &suggestBrush,
        ori[0] + space*x + stoneSpace, ori[1] + space*y + stoneSpace,
        space - stoneSpace * 2, space - stoneSpace * 2
    );    
}