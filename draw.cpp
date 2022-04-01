#include <windows.h>
#include <gdiplus.h>
#include "draw.h"
using namespace Gdiplus;

const int boardSize = 480, space = boardSize / 8;
const int wndWidth = 1120, wndHeight = 630;

const int ori[] = {(wndWidth - boardSize)/2, (wndHeight - boardSize)/2};

void DrawBase(HDC hdc){
    Gdiplus::Graphics graphics(hdc);
    Gdiplus::SolidBrush baseGreen(Gdiplus::Color(255, 0, 100, 0));
    
    graphics.FillRectangle(&baseGreen, ori[0], ori[1], boardSize, boardSize);

    Gdiplus::Pen linePen0(Gdiplus::Color(255, 0, 0, 0), 2);
    for(int i = 0; i < 9; i++){
        graphics.DrawLine(&linePen0, ori[0] + space*i, ori[1], ori[0] + space*i, ori[1] + boardSize);
    }
    for(int i = 0; i < 9; i++){
        graphics.DrawLine(&linePen0, ori[0], ori[1] + space*i, ori[0] + boardSize, ori[1] + space*i);
    }
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

void SuggestPos(HDC hdc, int x, int y, int score){
    Gdiplus::Graphics graphics(hdc);

    
    Gdiplus::FontFamily fontFamily(L"arial");
    Gdiplus::Font font(&fontFamily, space, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    Gdiplus::PointF pointF(ori[0] + space*x, ori[1] + space*y);
    Gdiplus::SolidBrush debugBrush(Gdiplus::Color(255, 0, 0, 0));

    switch(score){
        case 0:
            graphics.DrawString(L"0", -1, &font, pointF, &debugBrush);
            break;
        case 1:
            graphics.DrawString(L"1", -1, &font, pointF, &debugBrush);
            break;
        case 2:
            graphics.DrawString(L"2", -1, &font, pointF, &debugBrush);
            break;
        case 3:
            graphics.DrawString(L"3", -1, &font, pointF, &debugBrush);
            break;
        default:
            graphics.DrawString(L"-1", -1, &font, pointF, &debugBrush);
    }
    
}