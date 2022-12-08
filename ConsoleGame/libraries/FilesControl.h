#ifndef FILECONTROL_H
#define FILECONTROL_H 1

#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>
#include <io.h>

void get_path(std::string& path);
void getFiles(const std::string& path, std::vector<std::string>& files);
void getFiles(const std::string& path, std::set<std::string>& files);

void get_path(std::string& path) {
    char Full_path[_MAX_PATH];
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    _splitpath(_pgmptr, drive, dir, nullptr, nullptr);
    _makepath(Full_path, drive, dir, nullptr, nullptr);
    (path = std::string(Full_path)).pop_back();
}

void getFiles(const std::string& path, std::vector<std::string>& files) {
    //文件句柄
    long hFile = 0;
    //文件信息
    _finddata_t fileinfo;
    std::string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {  // _A_SUBDIR == 資料夾屬性(定義在io.h)
                // dfs先把某個資料夾找完，再用_findclose把這個資料夾關掉
                // 每個資料夾都會有.和..，分別代表當前目錄與下個目錄(不排除會遞迴不完)
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            } else {
                // 只要不是資料夾就是檔案，把它加進去vector
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

void getFiles(const std::string& path, std::set<std::string>& files) {
    long hFile = 0;
    _finddata_t fileinfo;
    std::string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            } else {
                files.insert(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

#endif