#include "parser.h"
#include "lexer.h"
#include "symbol.h"
#include "token.h"

#include <iostream>
#include <algorithm>

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

#ifndef TERMINAL_SYMBOLS
    #define TERMINAL_SYMBOLS
    #define END_OF_FILE -1
    //Accepting states
    #define RESERVED 101
    #define IDENTIFIER 102
    #define LIBRARY 103
    #define COMMENTARY 104
    #define INTEGER 105
    #define FLOAT 106
    #define FLOATSCI 107
    #define CHARACTER 108
    #define STRING 109
    #define TIMES_SIGN 110
    #define OVER_SIGN 111
    #define PLUS_SIGN 112
    #define MINUS_SIGN 113
    #define MODULO 114
    #define OR 115
    #define AND 116
    #define NOT 117
    #define LESSTHAN 118
    #define LESSEQUALS 119
    #define GREATERTHAN 120
    #define GREATEREQUALS 121
    #define EQUALS 122
    #define NEQUALS 123
    #define EQUAL_SIGN 124
    #define POINT 125
    #define COMMA 126
    #define COLON 127
    #define SEMICOLON 128
    #define PARENTHESISOPEN 129
    #define PARENTHESISCLOSE 130
    #define BRACKETSOPEN 131
    #define BRACKETSCLOSE 132
    #define SQUAREBOPEN 133
    #define SQUAREBCLOSE 134
    //Error states
    #define ERRORIDENTIFIER 501
    #define ERRORLIBRARY 502
    #define ERRORFLOAT 503
    #define ERRORFLOATSCI 504
    #define ERRORCHAR 505
    #define ERROROR 506
    #define ERRORAND 507
    #define ERRORUNKNOWN 599
#endif
#ifndef PARSER_FUNC
#define PARSER_FUNC
    #define IS_ERROR(A) A.grammeme >= 500
#endif

static int prediction[32][60] = {
    {0,   601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 0,   601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {2,   601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 1,   601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 4,   3,   601, 601, 601, 601, 601, 601, 4,   601, 601, 601, 4,   601, 601, 4,   601, 601, 601, 601, 601, 4,   4,   4,   601, 4,   601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 5,   601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 7,   601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 6,   601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 8,   9,   10,  11,  12,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 14,  601, 601, 601, 601, 601, 601, 601, 13,  14,  601, 14,  13,  601, 14,  13,  14,  601, 601, 601, 601, 13,  13,  13,  601, 13,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 16,  601, 601, 601, 18,  601, 601, 17,  601, 601, 601, 601, 601, 19,  20,  21,  601, 15,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 22,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 23,  601, 601, 23,  23,  23,  23,  23,  601, 601, 601, 601, 601, 601, 601, 23,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 23,  601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 24,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 25,  601, 25,  601, 25,  601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 26,  601, 601, 26,  26,  26,  26,  26,  601, 601, 601, 601, 601, 601, 601, 26,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 26,  601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 27,  601, 601, 601, 601, 601, 601, 601, 601, 601, 28,  601, 28,  601, 28,  601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 29,  601, 601, 29,  29,  29,  29,  29,  601, 601, 601, 601, 601, 601, 601, 29,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 29,  601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 31,  601, 601, 31,  31,  31,  31,  31,  601, 601, 601, 601, 601, 601, 601, 30,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 31,  601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 32,  601, 601, 32,  32,  32,  32,  32,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 32,  601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 34,  34,  601, 33,  33,  33,  33,  33,  33,  601, 601, 34,  601, 34,  601, 34,  601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 37,  38,  39,  40,  35,  36,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 41,  601, 601, 41,  41,  41,  41,  41,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 41,  601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 42,  43,  601, 44,  44,  601, 44,  44,  44,  44,  44,  44,  601, 601, 44,  601, 44,  601, 44,  601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 45,  601, 601, 45,  45,  45,  45,  45,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 45,  601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 46,  47,  49,  49,  48,  49,  49,  601, 49,  49,  49,  49,  49,  49,  601, 601, 49,  601, 49,  601, 49,  601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 50,  601, 601, 51,  52,  53,  54,  55,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 56,  601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 57,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 58,  601, 59,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 60,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 61,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 62,  601, 601, 62,  62,  62,  62,  62,  601, 601, 601, 601, 601, 601, 601, 62,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 62,  601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 63,  601, 601, 601, 64,  601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 65,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 66,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601},
    {601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 67,  601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601, 601}
};

bool compare(Symbol, Token);

Parser::Parser() {
    lexer = new Lexer();
}

void Parser::step() {
    Symbol top = symbols.back();
    int column = Symbol::hash(token.grammeme, token.lexeme);
    int row = top.grammeme;
    int production = prediction[row][column];
    symbols.pop_back();
    for (Symbol s: Symbol::derive(production)) {
        symbols.push_back(s);
    }
}

bool Parser::transduce(std::string &text) {
    restart();
    Symbol program = Symbol(PROGRAM, false);
    Symbol eof = Symbol(END_OF_FILE, true);
    symbols.push_back(eof);
    symbols.push_back(program);
    // Look through the entire text
    bool next = false;
    Symbol top;
    for (unsigned int i = 0; i < text.length(); i++) {
        token = lexer->generateToken(i, text);
        next = false;
        while (!next) {
            top = symbols.back();
            if (IS_ERROR(token)) {
                // Lexical error
                error = "Lexical error";
                return false;
            } else if (compare(top, token)) {
                symbols.pop_back();
                next = true;
            } else if (symbols.back().terminal) {
                // Syntactical error
                error = "Syntactical error, non matching terminal";
                return false;
            }   else if (isValidDerivation()) {
                step();
            } else {
                // Syntactical error
                error = "Syntactical error, not valid derivation";
                return false;
            }
        }
    }
    if (symbols.empty()) return true;
    else return false;
}

bool Parser::isValidDerivation() {
    int column = Symbol::hash(token.grammeme, token.lexeme);
    int row = symbols.back().grammeme;
    int production = prediction[row][column];
    return production < 600;
}

bool compare(Symbol symbol, Token token) {
    if (symbol.terminal) {
        return symbol.grammeme == Symbol::hash(token.grammeme, token.lexeme);
    } else {
        return false;
    }
}

void Parser::restart() {
    lexer->restart();
    symbols.clear();
}
