#pragma once

namespace Syntax {

struct Token {
    enum Type {
        WHITESPACE = 0, // only used for displaying
        SYMBOL = 1, // =, >=, <=, !=
        STRING = 2, // expression encased by "/'
        VALUE = 3, // expression surrounded by $
        EXPRESSION =4, // a word not of the prev types
        SCOPE_OPEN = 5, // {
        SCOPE_CLOSE = 6, // }
    }
};


}