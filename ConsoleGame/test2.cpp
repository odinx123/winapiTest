#include <iostream>

#include "libraries/MyFunction.h"
using namespace std;

#define WIDTH 95
#define HEIGHT 40

int main() {
    // Game game(WIDTH, HEIGHT);

    string s;

    while (cin >> s) {
        cout << s << endl;
        if (s == "我")
            cout << "true" << endl;
        // if (game.EventType() == MOUSE_EVENT) {
        //     switch (game.getMouseEvent()) {
        //         case LEFTCLICK:
        //             cout << "left click " << game.getMousePosition().X << " " << game.getMousePosition().Y;
        //             cout << endl;
        //             break;
        //         case RIGHTCLICK:
        //             cout << "right click " << game.getMousePosition().X << " " << game.getMousePosition().Y;
        //             cout << endl;
        //             break;
        //         case MIDDLECLICK:
        //             cout << "middle click " << game.getMousePosition().X << " " << game.getMousePosition().Y;
        //             cout << endl;
        //             break;
        //     }
        // }
        // setfps(60);
    }

    return 0;
}