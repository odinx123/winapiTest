#include <fstream>
#include <iostream>
#include <windows.h>
#include <fcntl.h>
#include <codecvt>
using namespace std;

#define WIDTH 95
#define HEIGHT 40

int main() {
    SetConsoleOutputCP(65001);
    _setmode(_fileno(stdout), _O_U16TEXT);

    wifstream file_in("map/test.txt");
    if (file_in.fail()) {
        cout << "失敗" << endl;
        return 0;
    }

    ofstream file_out("./map/test.txt");

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j)
            if (i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1)
                file_out << "⏺";
            else
                file_out << ' ';
        file_out << endl;
    }

    system("pause");
    return 0;
}