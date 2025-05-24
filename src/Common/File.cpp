#include "Common/File.hpp"

using namespace Common;
namespace fs = std::filesystem;


bool Filesystem::exists(const std::string& path){
    fs::path p = fs::weakly_canonical(path);
    std::cout << "Full Path: " << p << std::endl;
    return fs::exists(p); 
}

Common::TrackedCursor Filesystem::open(const std::string& path) {
    
    if (!exists(path)){
        return TrackedCursor();
    }

    fs::path p = fs::weakly_canonical(path);

    TrackedCursor cursor;
    cursor.path = p.string();
    // cursor.filename

    std::ifstream file(p);
  
	// infile.open("shellcode.bin", std::ios::in | std::ios::binary);  
	file.seekg(0, std::ios::end);  
  
	size_t file_size_in_byte = file.tellg();  
	cursor.content = (char*)malloc(sizeof(char) * file_size_in_byte);  
  
	file.seekg(0, std::ios::beg);  
	file.read(cursor.content, file_size_in_byte);  
  
	// printf("%s\n", cursor.content); // << prints content of cursor.content after load from file  
  
	if (file.eof()) {  
		size_t bytes_really_read = file.gcount();  
        cursor.length = bytes_really_read;
	}  
	else if (file.fail()) {
        std::cerr << "Error reading file" << std::endl;
    }  

    std::cout << "File read with length of \n\t=> " << cursor.length << " charachters" << std::endl;

	file.close();
    cursor.position = 0;
    cursors.push_back(cursor);
    return cursor;
    
    // if (!file) {
    //     throw std::runtime_error("Failed to open file: " + path);
    // }

    // std::ostringstream ss;
    // ss << file.rdbuf();

    // Cursor cursor;
    // cursor.buffer = ss.str();
    // cursor.view = cursor.buffer;
    // cursor.position = 0;
    // return cursor;
}