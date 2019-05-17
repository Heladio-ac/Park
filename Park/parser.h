#ifndef PARSER_H
#define PARSER_H

#include <stack>

class Lexer;
class Symbol;
class Parser {
public:
    Lexer *lexer;
    std::stack<Symbol> symbols;

};

#endif
