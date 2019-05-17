#ifndef LEXER_H
#define LEXER_H

#include <string>

class Token;
class Error;

class Lexer {
public:
    int state;
    std::string lexeme;

    Lexer();
    void step(char symbol);
    Token generateToken(int &index, std::string &text);

    int hash(char symbol);
    void restart();
    bool isFinal();
    bool isReserved();
};

#endif // LEXER_H
