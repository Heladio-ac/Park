#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <string>

class Lexer;
class Symbol;
class Token;

class Parser {
public:
    Lexer *lexer;
    std::list<Symbol> symbols;
    Token token;

    Parser();
    void step(Symbol);
    void transduce(std::string &text);

    int hash(int);  //Hashes a number encoding the grammeme to a column index for the predictive matrix
    bool compare(Symbol, Token);
};

#endif
