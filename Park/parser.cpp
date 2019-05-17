#include "parser.h"

#include "lexer.h"
#include "symbol.h"
#include "token.h"

#ifndef PRODUCTIONS
#define PRODUCTIONS
    #define EXPRESSION
    #define END_FILE
#endif

Parser::Parser() {

}

void Parser::step(Symbol symbol) {
    for (Symbol s: Symbol::derive(symbol)) {
        symbols.push_back(s);
    }
}

void Parser::transduce(std::string &text) {
    symbols.push_back(Symbol(END_FILE));
    symbols.push_back(Symbol(EXPRESSION));
    for (int i = 0; i < text.length(); i++) {
        if (compare(symbols.back(), lexer->generateToken(i, text))) {

        }
        symbols.pop_back();
    }
}

bool Parser::compare(Symbol symbol, Token token) {
    // Determine wheter the symbol is a final element which coincides with the token's grammeme
}
