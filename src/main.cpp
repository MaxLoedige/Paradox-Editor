#include "Common/FileInterface.hpp"

#include <iostream>

int main(){

    // std::cout << "Hello world" << std::endl;
    auto interface = Common::FileInterface();
    
    bool exists = interface.exits("30_activity_decisions.txt");

    std::cout << "Exists " << exists << std::endl;

    try {
        Common::Cursor cursor = interface.open("30_activity_decisions.txt");

        while (!cursor.eof()) {
            auto token = cursor.next();
            if (!token.empty())
                std::cout << "[" << token << "]\n";
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
    }

}