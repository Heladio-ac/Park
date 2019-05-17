#ifndef LEXER_H
#define LEXER_H

#include <string>

class Token;
class Error;
class Lexer {
public:
    int state;
    std::string lexeme;

public:
    Lexer();
    void step(char symbol);
    Token generateToken(int &index, std::string &text);

    int hash(char symbol);
    void restart();
    bool isValid();
    bool isDelimiter();
    bool isFinal();
    bool isReserved();
    int getstate();
};

#endif // LEXER_H
