#include "Common/File.hpp"

#include <iostream>

int main(){

    // std::cout << "Hello world" << std::endl;
    auto interface = Common::Filesystem();
    
    bool exists = interface.exists("30_activity_decisions.txt");

    std::cout << "Exists " << exists << std::endl;

    try {
        Common::TrackedCursor cursor = interface.open("30_activity_decisions.txt");

        while (!cursor.eof()) {
            std::cout << cursor.current();
            ++cursor;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
    }

}