#include "symbol.h"

#ifndef NON_TERMINAL_SYMBOLS
#define NON_TERMINAL_SYMBOLS
    #define PROGRAM 0
    #define DECL_LIBRARIES 1
    #define DECL_VARIABLES 2
    #define VARIABLES 3
    #define MORE_VARIABLES 4
    #define TYPE 5
    #define STATEMENTS 6
    #define STATEMENT 7
    #define ASSIGNMENT 8
    #define EXPRESSION_0 9
    #define DISJUNCTION 10
    #define EXPRESSION_1 11
    #define CONJUNCTION 12
    #define EXPRESSION_2 13
    #define NEGATION 14
    #define EXPRESSION_3 15
    #define COMPARISON 16
    #define RELATIONAL_OPERATOR 17
    #define EXPRESSION_4 18
    #define ADDITION 19
    #define ADDEND 20
    #define MULTIPLICATION 21
    #define FACTOR 22
    #define IF 23
    #define ELSE 24
    #define WHILE 25
    #define FOR 26
    #define EXPRESSIONS 27
    #define MORE_EXPRESSIONS 28
    #define READ 29
    #define WRITE 30
    #define ENTER 31
#endif

Symbol::Symbol(int g) {
    grammeme = g;
}

std::list<Symbol> Symbol::derive(int production) {
    std::list<Symbol> symbols;
    switch (production) {
        case PROGRAM:
            symbols.push_back();
        default:
    }
    return symbols;
}
