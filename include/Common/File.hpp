#pragma once

#include <string>
#include <vector>
#include <fstream> 
#include <filesystem>
#include <iostream>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <atomic>


namespace fs = std::filesystem;

// ======= File Interface =======
// The file interface is responsible for loading and saving files
// and giving excess to easy to use cursors

namespace Common {

// lightweight wrapper around an open file, 
// can be used to write and read data
struct TrackedCursor {

    std::string path;
    std::string filename;
    
    char* content; 
    size_t length;
    size_t position;

    // TrackedCursor(const TrackedCursor& other){

    // }
    // TrackedCursor operator=(const TrackedCursor& other){

    // }

    ~TrackedCursor(){
        // count and delete content if it is not used anywhere anymore
        // delete[] content;
    }

    char current() const {
        return *(content + position);
    }

    bool eof() const {
        return position >= length;
    }

    void operator++() {
        if (!eof()) ++position;
    }

    // save
    void save(){

    }

    // Tracked Properties

private:
    
    std::atomic_size_t* count;
};

struct Filesystem {
    bool exists(const std::string& path);

    TrackedCursor open(const std::string& path);

    ~Filesystem(){
        for (auto c : cursors){
            delete[] c.content;
        }
    }

    std::vector<TrackedCursor> cursors;
};

}