#ifndef MAP_H
#define MAP_H 1

#include <windows.h>

#include <codecvt>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <boost/unordered_set.hpp>
#include "FilesControl.h"
#include "screen.h"

std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);

class Map : public Screen {
   private:
    std::string path;
    std::wifstream file_in;
    std::set<std::string> mapName;

   protected:
    WORD color;
    boost::unordered_set<std::pair<SHORT, SHORT>> obj;

   public:
    // Constructor
    Map() = default;
    Map(SHORT Width, SHORT Height);

    // Function
    void loadMap(const std::string& name);
    void setInfo(const std::string& title, const std::string& info, SHORT x, SHORT y, WORD cor);
    void printInfo(const std::string& info, SHORT x, SHORT y, WORD cor);
    bool isMapObj(const wpicture& pic, SHORT x, SHORT y);
    void clear();
};

Map::Map(SHORT Width, SHORT Height) : Screen(Width, Height) {
    get_path(path);
    path += "\\map";
    getFiles(path, mapName);
    file_in.imbue(loc);
}

void Map::loadMap(const std::string& name) {
    Screen::SetColor();
    std::string full_path = path + "\\" + name + ".txt";
    if (mapName.count(full_path) <= 0) {
        printInfo("地圖不存在!!!", 3, 1, 79);
        return;
    }
    printInfo(" ", 3, 1, 7);
    setInfo("地圖資訊", name, 3, 1, 95);

    file_in.open(full_path);
    for (int i = 0; i < height; ++i)
        getline(file_in, curMap[i]);
    file_in >> color;
    file_in.close();

    obj.clear();
    for (SHORT i = 0; i < height; ++i) {
        for (SHORT j = 0; j < width; ++j) {
            if (curMap[i][j] != L' ')
                obj.insert(std::make_pair(j, i));
        }
    }
    Screen::SetColor(color);
}

void Map::clear() {
    for (SHORT i = 0; i < height; ++i) {
        for (SHORT j = 0; j < width; ++j) {
            if (obj.count(std::make_pair(j, i)) <= 0)
                curMap[i][j] = L' ';
        }
    }
}

void Map::setInfo(const std::string& title, const std::string& info, SHORT x, SHORT y, WORD cor) {
    SetColor(cor);
    setInfoCursorPos(x, y);
    std::cout << title << ":";
    printInfo(info, title.size()+1, y, cor);
    SetColor(color);
}

void Map::printInfo(const std::string& info, SHORT x, SHORT y, WORD cor) {
    SetColor(cor);
    SHORT gap = infoWidth - x, times = 0, size_;
    if (gap < 0) return;
    if (gap < info.size()) {
        times = info.size() / gap + 1;
        for (SHORT i = 0; i < times; ++i) {
            setInfoCursorPos(x, y+i);
            size_ = info.size()-(i+1)*gap >= 0 ? gap : info.size()-i*gap;
            std::cout << info.substr(i*gap, size_);
        }
        std::cout << std::string(infoWidth-size_, ' ');
    } else {
        setInfoCursorPos(x, y);
        std::cout << info;
        SetColor();
        std::cout << std::string(gap-info.size()-1, ' ');
    }
    SetColor(color);
    display();
}

bool Map::isMapObj(const wpicture& pic, SHORT x, SHORT y) {
    for (int i = 0; i < pic.size(); ++i) {
        for (int j = 0; j < pic[i].size(); ++j) {
            if (obj.count(std::make_pair(x+j, y+i)) > 0)
                return true;
        }
    }
    return false;
}

#endif