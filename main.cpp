#include "draw.h"
#include <vector>
#include <cassert>
using namespace Gdiplus;

int boardState = 0;
std::vector<std::vector<int>> level = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, 0, 1, -1, -1, -1},
    {-1, -1, -1, 1, 0, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1}
};

VOID TestPaint(HDC hdc){
    Gdiplus::Graphics graphics(hdc);

    //window: 1120 × 630
    int boardSize = 480;
    Gdiplus::SolidBrush baseGreen(Gdiplus::Color(255, 0, 100, 0));
    int ori[] = {(1120 - boardSize)/2, (630 - boardSize)/2};
    
    if(boardState == 0){
        DrawBase(hdc);
        boardState++;
    }
    

    Gdiplus::Pen linePen0(Gdiplus::Color(255, 0, 0, 0), 2);
    int space = boardSize / 8;

    for(int i = 0; i < 9; i++){
        graphics.DrawLine(&linePen0, ori[0] + space*i, ori[1], ori[0] + space*i, ori[1] + boardSize);
    }
    for(int i = 0; i < 9; i++){
        int space = boardSize / 8;
        graphics.DrawLine(&linePen0, ori[0], ori[1] + space*i, ori[0] + boardSize, ori[1] + space*i);
    }

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            int state = level.at(i).at(j);
            DrawStone(hdc, i, j, state);
        }
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
    HDC hdc;
    PAINTSTRUCT paintStruct;

    switch(msg){
    case WM_DESTROY:
        MessageBox(hwnd, TEXT("Bye"), TEXT("End Msg"), MB_ICONSTOP);
        PostQuitMessage(0);
        return 0;
    case WM_LBUTTONUP:
        PostMessage(hwnd, WM_PAINT, wp, lp);
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &paintStruct);
        TestPaint(hdc);
        EndPaint(hwnd, &paintStruct);
        return 0;
    default: 
        return DefWindowProc(hwnd, msg, wp, lp);
    }
    
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow){
    WNDCLASS winc;
    MSG msg;
    Gdiplus::GdiplusStartupInput gdiplusStartInput;
    ULONG_PTR gdiplusToken;

    GdiplusStartup(&gdiplusToken, &gdiplusStartInput, NULL);

    winc.style = CS_HREDRAW || CS_VREDRAW;
    winc.lpfnWndProc = WndProc;
    winc.cbClsExtra = 0;
    winc.cbWndExtra = 0;
    winc.hInstance = hInstance;
    winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    winc.hCursor = LoadCursor(NULL, IDC_ARROW);
    winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    winc.lpszMenuName = NULL;
    winc.lpszClassName = TEXT("Nemu");

    if(!RegisterClass(&winc)) return 0;

    HWND hwnd = CreateWindow(
        TEXT("Nemu"), TEXT("My First Window"),
        WS_OVERLAPPEDWINDOW,
        0, 0, 1120, 630 + 36,
        NULL, NULL,
        hInstance, NULL
    );

    if(hwnd == NULL) return 0;

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    
    while(GetMessage(&msg, NULL, 0, 0)){
        DispatchMessage(&msg);
    }
    
    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}

