#pragma once

#include <string>
#include <vector>
#include <fstream> 
#include <filesystem>
#include <iostream>
#include <sstream>
#include <cctype>
#include <stdexcept>


namespace fs = std::filesystem;

// ======= File Interface =======
// The file interface is responsible for loading and saving files
// and giving excess to easy to use cursors

namespace Common {

struct Cursor;

struct FileInterface {

    FileInterface() {}

    Cursor open(const std::string& path);

    bool exits(const std::string& path);

private:
    std::vector<Cursor> m_files;

};

// lightweight wrapper around an open file 
struct Cursor {
    std::string buffer;
    std::string_view view;
    size_t length;
    size_t position;

    char current() const {
        return (position < view.size()) ? view[position] : '\0';
    }
    bool eof() const {
        return position >= view.size();
    }
    void advance() {
        if (!eof()) ++position;
    }
    void skipWhitespace() {
        while (!eof() && std::isspace(static_cast<unsigned char>(current())))
            advance();
    }
    std::string_view next() {
        skipWhitespace();
        if (eof()) return {};

        char c = current();

        // Handle quoted strings ("..." or '...')
        if (c == '"' || c == '\'') {
            char quote = c;
            size_t start = position++;
            while (!eof()) {
                char ch = current();
                if (ch == quote) {
                    ++position;
                    break;
                }
                advance();
            }
            return view.substr(start, position - start); // includes quotes
        }

        // Return delimiters as single-char tokens
        if (c == '=' || c == '{' || c == '}') {
            ++position;
            return view.substr(position - 1, 1);
        }

        // Return regular token
        size_t start = position;
        while (!eof()) {
            char ch = current();
            if (std::isspace(static_cast<unsigned char>(ch)) ||
                ch == '=' || ch == '{' || ch == '}' || ch == '"' || ch == '\'') {
                break;
            }
            advance();
        }

        return view.substr(start, position - start);
    }
};

// Basic token types 
struct Token {
    
    enum TokenType {
        
    };
    
    TokenType type;
    std::string_view content;
};

}