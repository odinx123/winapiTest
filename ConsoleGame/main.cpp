#include <conio.h>
#include <windows.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "libraries/MyFunction.h"

#define WIDTH 95
#define HEIGHT 40

std::stringstream stream;

void command(Game& game);

int main() {
    Game game(WIDTH, HEIGHT);
    game.setConsoleName(L"C110152318期末作業⚔⛊");
    game.loadMap("lobby");

    std::vector<Object> obj;
    wpicture p(1, wpix(1, L'☹'));

    Object person(p, 10, 5, 2);
    person.bindGame(&game);
    person.setPos(game.getWidth() / 2, game.getHeight() / 2);

    // system("pause");
    while (true) {
        int temp;
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            temp = person.move(0, -0.2);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            temp = person.move(0, 0.2);
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            temp = person.move(0.5, 0);
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            temp = person.move(-0.5, 0);
        }
        if (_kbhit()) {
            char c = _getch();
            if (c == 47) {
                command(game);
            } else if (c == 27) {
                game.setGameState(true);
                game.printInfo(std::to_string(c), 4, 4, 7);
            }
            // game.printInfo(std::to_string(c), 4, 4, 7);
        }
        game.clear();
        person.draw();
        game.display();
        setfps(30);
    }

    return 0;
}

void command(Game& game) {
    std::string temp, ins, name;
    game.printInfo("請輸入指令!!!", 3, 20, 7);
    game.setCursorVisable(true);

    game.setInfoCursorPos(3, 21);
    game.SetColor();
    std::getline(std::cin, temp);
    if (temp[0] == '\n') return;
    stream.clear();
    stream.str(temp);
    stream >> ins;
    if (ins == "mov") {
        stream >> name;
        game.loadMap(name);
    }
    game.printInfo(" ", 3, 20, 7);
    game.printInfo(" ", 3, 21, 7);
    game.setCursorVisable(false);
}