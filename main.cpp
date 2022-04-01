#include "draw.h"
#include "board.h"
#include <windowsx.h>

using namespace Gdiplus;

std::vector<int> clickPos = {0, 0};
Board board;


VOID TestPaint(HDC hdc){
    Gdiplus::Graphics graphics(hdc);
    Gdiplus::SolidBrush baseGreen(Gdiplus::Color(255, 0, 100, 0));
    const int boardSize = 480, space = boardSize / 8;
    const int ori[] = {(1120 - boardSize)/2, (630 - boardSize)/2};
    //window: 1120 × 630
    
    DrawBase(hdc);
   
    std::vector<int> posOnBoard = {clickPos[0] - ori[0], clickPos[1] - ori[1]};
    std::vector<int> tile = {posOnBoard[0] / space, posOnBoard[1] / space};
    board.PutStone(tile[0], tile[1]);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            DrawStone(hdc, i, j, board.GetTileState(i, j));
            board.CalcTileScore(i, j);
            
            if(board.GetTileState(i, j) >= 0) continue;
            SuggestPos(hdc, i, j, board.GetTileScore(i, j));
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
        clickPos[0] = GET_X_LPARAM(lp);
        clickPos[1] = GET_Y_LPARAM(lp);
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