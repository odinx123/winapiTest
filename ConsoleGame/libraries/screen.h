#ifndef SCREEN_H
#define SCREEN_H 1

#define LEFTCLICK FROM_LEFT_1ST_BUTTON_PRESSED
#define RIGHTCLICK RIGHTMOST_BUTTON_PRESSED
#define MIDDLECLICK FROM_LEFT_2ND_BUTTON_PRESSED

#include <vector>
#include <windows.h>
#include "ScreenFunction.h"

typedef std::wstring wpix;
typedef std::vector<wpix> wpicture;

class Screen {
   private:
    HANDLE stdBuf;
    HANDLE stdInpt;
    COORD orgPos;
    COORD infoOrgPos;
    INPUT_RECORD inputRec;
    CONSOLE_CURSOR_INFO cursorInfo;
    CONSOLE_SCREEN_BUFFER_INFO winInfo;

   protected:
    SHORT width;
    SHORT height;
    SHORT infoWidth;
    wpicture curMap;
   
   public:
    // Constructor
    Screen() = default;
    Screen(SHORT Width, SHORT Height);

    // function

    inline void setOrgPosition(SHORT x, SHORT y);
    void draw(const wpicture& pic, SHORT x, SHORT y);
    void display() const;
    inline void setConsoleName(const wpix& name) const;
    SHORT getWidth() const { return width; }
    SHORT getHeight() const { return height; }
    inline void SetColor(WORD color = 7) const;
    inline void setCursorPos(SHORT x, SHORT y) const ;
    inline void setInfoCursorPos(SHORT x, SHORT y) const;
    inline COORD getCurrenCursorInfo();
    inline SHORT getConsoleWidth();
    // Every read not the same.
    inline WORD EventType();
    inline DWORD getMouseEvent() const;
    inline COORD getMousePosition() const;
    // To judge not the keyUp.
    inline WINBOOL isKeyDown() const;
    inline int getKeyCode() const;
    inline int getKeyAscii() const;
    inline void setCursorVisable(bool state);
};

// constructor

Screen::Screen(SHORT Width, SHORT Height) {
    // todo
    width = Width;
    height = Height;

    orgPos = COORD{0, 0};
    infoOrgPos.Y = 0;
    infoOrgPos.X = width + 1;
    curMap.resize(height, wpix(width, ' '));

    stdBuf = GetStdHandle(STD_OUTPUT_HANDLE);
    stdInpt = GetStdHandle(STD_INPUT_HANDLE);
    infoWidth = getConsoleWidth() - width;

    cursorInfo = {1, false};
    SetConsoleCursorInfo(stdBuf, &cursorInfo);

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 300, 35, 0, 0, SWP_NOSIZE);

    // DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    // SetConsoleMode(stdInpt, fdwMode);
}

// Function

void Screen::setOrgPosition(SHORT x, SHORT y) {
    orgPos.X = x;
    orgPos.Y = y;
}

void Screen::draw(const wpicture& pic, SHORT x, SHORT y) {
    SHORT yLength = height >= pic.size()+y ? pic.size()+y : height;
    SHORT xLength = width >= pic[0].size()+x ? pic[0].size()+x : width;
    for (SHORT i = y; i < yLength; ++i) {
        for (int j = x; j < xLength; ++j)
            curMap[i][j] = pic[i-y][j-x];
    }
}

void Screen::setConsoleName(const wpix& name) const {
    SetConsoleTitleW(name.c_str());
}

void Screen::display() const {
    for (SHORT i = 0; i < height; ++i) {
        setCursorPos(0, i);
        WriteConsoleW(stdBuf, curMap[i].c_str(), width, nullptr, nullptr);
    }
}

void Screen::setCursorPos(SHORT x, SHORT y) const {
    SHORT tx = orgPos.X + x, ty = orgPos.Y + y;
    SetConsoleCursorPosition(stdBuf, {tx, ty});
}

void Screen::SetColor(WORD color) const {
    SetConsoleTextAttribute(stdBuf, color);
}

void Screen::setInfoCursorPos(SHORT x, SHORT y) const {
    SHORT tx = infoOrgPos.X + x, ty = infoOrgPos.Y + y;
    SetConsoleCursorPosition(stdBuf, {tx, ty});
}

COORD Screen::getCurrenCursorInfo() {
    GetConsoleScreenBufferInfo(stdBuf, &winInfo);
    return winInfo.dwCursorPosition;
}

SHORT Screen::getConsoleWidth() {
    GetConsoleScreenBufferInfo(stdBuf, &winInfo);
    return winInfo.dwSize.X;
}

WORD Screen::EventType() {
    DWORD temp;
    ReadConsoleInput(stdInpt, &inputRec, 1, &temp);
    return inputRec.EventType;
}

DWORD Screen::getMouseEvent() const {
    return inputRec.Event.MouseEvent.dwButtonState;
}

COORD Screen::getMousePosition() const {
    return inputRec.Event.MouseEvent.dwMousePosition;
}

WINBOOL Screen::isKeyDown() const {
    return inputRec.Event.KeyEvent.bKeyDown;
}

int Screen::getKeyCode() const {
    if (isKeyDown())
        return inputRec.Event.KeyEvent.wVirtualKeyCode;
    return -1;
}

int Screen::getKeyAscii() const {
    return inputRec.Event.KeyEvent.uChar.AsciiChar;
}

void Screen::setCursorVisable(bool state) {
    cursorInfo = {1, state};
    SetConsoleCursorInfo(stdBuf, &cursorInfo);
}

#endif