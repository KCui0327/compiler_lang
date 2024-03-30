#include <iostream>
#include <string>
#include "lexer.hpp"

static int gettok() {
    static int last_char = ' ';

    while (std::isspace(last_char)) {
        last_char = getchar();
    }

    if (std::isalpha(last_char)) {
        identifier_str = last_char;
        while (std::isalnum((last_char = getchar()))) {
            identifier_str += last_char;
        }

        if (identifier_str == "def") {
            return tok_def;
        } else if (identifier_str == "extern") {
            return tok_extern;
        }

        return tok_identifier;
    }

    if (std::isdigit(last_char) || last_char == '.') {
        std::string num_str;

        do {
            num_str += last_char;
            last_char = getchar();
        } while (std::isdigit(last_char) || last_char == '.');

        num_val = strtod(num_str.c_str(), 0);
        return tok_number;
    }

    if (last_char == '#') {
        do {
            last_char = getchar();
        } while (last_char != EOF && last_char != '\n' && last_char != '\r');

        if (last_char != EOF) {
            return gettok();
        }
    }

    if (last_char == EOF) {
        return tok_eof;
    }

    int this_char = last_char;
    last_char = getchar();
    return this_char;
}