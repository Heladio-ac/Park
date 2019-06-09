#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#include <ctype.h>
#include <algorithm>
#include <initializer_list>
#include <string>

class Token;

class Lexer {
public:
    int state;
    std::string lexeme;

    Lexer();
    void step(char symbol);
    Token generateToken(unsigned int &index, std::string &text);

    int hash(char symbol);
    void restart();
    bool isFinal();
};

#endif // LEXER_H
