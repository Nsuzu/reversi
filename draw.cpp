#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

const int boardSize = 480, space = boardSize / 8;
const int wndWidth = 1120, wndHeight = 630;

const int ori[] = {(wndWidth - boardSize)/2, (wndHeight - boardSize)/2};

void DrawBase(HDC hdc){
    Gdiplus::Graphics graphics(hdc);
    Gdiplus::SolidBrush baseGreen(Gdiplus::Color(255, 0, 100, 0));
    
    graphics.FillRectangle(&baseGreen, ori[0], ori[1], boardSize, boardSize);
}

void DrawStone(HDC hdc, int x, int y, int state){
    if(state < 0) return;
    const int stoneSpace = 5;

    Gdiplus::Graphics graphics(hdc);
    Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 255*state, 255*state, 255*state));

    graphics.FillEllipse(
        &whiteBrush,
        ori[0] + space*x + stoneSpace, ori[1] + space*y + stoneSpace,
        space - stoneSpace * 2, space - stoneSpace * 2
    );
}