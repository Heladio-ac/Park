#include "parser.h"

#include "lexer.h"
#include "symbol.h"
#include "token.h"

#ifndef PRODUCTIONS
#define PRODUCTIONS
    #define EXPRESSION
    #define END_FILE
#endif

#ifndef PARSER_FUNC
#define PARSER_FUNC
    #define IS_ERROR(A) A.grammeme >= 500
    #define COMPARE(A, B) A.grammeme == B.grammeme
#endif

static int prediction[1][1] = {
    {0}
};

Parser::Parser() {
    lexer = new Lexer();
}

void Parser::step(Symbol symbol) {
    for (Symbol s: Symbol::derive(symbol)) {
        symbols.push_back(s);
    }
}

void Parser::transduce(std::string &text) {
    symbols.push_back(Symbol(END_FILE));
    symbols.push_back(Symbol(EXPRESSION));
    // Look through the entire text
    for (int i = 0; i < text.length(); i++) {
        token = lexer->generateToken(i, text);
        if (IS_ERROR(token))
        if (COMPARE(symbols.back(), token)) {
            symbols.pop_back();
        } else if () {

        } else {
            //error
        }
    }
}
