#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <string>

#include "tree.hh"
#include "token.h"

class Lexer;
class Symbol;
class Parser {
public:
    Lexer* lexer;
    std::list<Symbol> symbols;
    Token token;
    std::string error;
    tree<std::string> syntaxTree;

    Parser();
    void step();
    void restart();
    bool transduce(std::string &text);
};

#endif
