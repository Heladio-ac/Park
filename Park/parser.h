#ifndef PARSER_H
#define PARSER_H

class Lexer;
class Parser {
public:
    Lexer *lexer;
    std::stack<Symbol> symbols;

public:
    void step;
}