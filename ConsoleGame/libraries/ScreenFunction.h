#ifndef SCREENFUNCTION_H
#define SCREENFUNCTION_H 1

#include <windows.h>

// Function declaration
void setConsoleSize(SHORT Width, SHORT Height, HANDLE buf);
void setfps(double timePerFrame);

// Function define
void setConsoleSize(SHORT Width, SHORT Height, HANDLE buf) {
    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
    COORD coord{Width, Height};
    SetConsoleScreenBufferSize(buf, coord);
    SetConsoleWindowInfo(buf, true, &Rect);
}

void setfps(double timePerFrame) {
    static DWORD lastTime = GetTickCount();
    timePerFrame = 1000.f / timePerFrame;
    DWORD nowTime = GetTickCount();
    DWORD deltaTime = nowTime - lastTime;
    lastTime = nowTime;
    if (deltaTime <= timePerFrame)
        Sleep(timePerFrame - deltaTime);
}

#endif