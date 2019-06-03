#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <string>
#include "token.h"

class Lexer;
class Symbol;
class Parser {
public:
    Lexer *lexer;
    std::list<Symbol> symbols;
    Token token;

    Parser();
    void step();
    void transduce(std::string &text);
    bool isValidDerivation();
};

#endif
