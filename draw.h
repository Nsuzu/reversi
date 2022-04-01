#ifndef DRAW_H
#define DRAW_H

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

void DrawBase(HDC);
void DrawStone(HDC, int, int, int);
void SuggestPos(HDC, int, int, int);

#endif