#include "Common/FileInterface.hpp"

using namespace Common;
namespace fs = std::filesystem;


bool FileInterface::exits(const std::string& path){
    fs::path p = fs::weakly_canonical(path);
    std::cout << "Full Path: " << p << std::endl;
    return fs::exists(p); 
}

Cursor FileInterface::open(const std::string& path) {
    
    if (!exits(path)){
        return Cursor();
    }

    fs::path p = fs::weakly_canonical(path);
    std::ifstream file(p);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::ostringstream ss;
    ss << file.rdbuf();

    Cursor cursor;
    cursor.buffer = ss.str();
    cursor.view = cursor.buffer;
    cursor.position = 0;
    return cursor;
}