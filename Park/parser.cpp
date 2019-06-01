#include "parser.h"
#include "lexer.h"
#include "symbol.h"
#include "token.h"

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
    //Accepting states
    #define RESERVED 101
    #define IDENTIFIER 102
    #define COMMENTARY 103
    #define INTEGER 104
    #define FLOAT 105
    #define FLOATSCI 106
    #define CHARACTER 107
    #define STRING 108
    #define TIMES_SIGN 109
    #define OVER_SIGN 110
    #define PLUS_SIGN 111
    #define MINUS_SIGN 112
    #define MODULO 113
    #define OR 114
    #define AND 115
    #define NOT 116
    #define LESSTHAN 117
    #define LESSEQUALS 118
    #define GREATERTHAN 119
    #define GREATEREQUALS 120
    #define EQUALS 121
    #define NEQUALS 122
    #define EQUAL_SIGN 123
    #define POINT 124
    #define COMMA 125
    #define COLON 126
    #define SEMICOLON 127
    #define PARENTHESISOPEN 128
    #define PARENTHESISCLOSE 129
    #define BRACKETSOPEN 130
    #define BRACKETSCLOSE 131
    #define SQUAREBOPEN 132
    #define SQUAREBCLOSE 133
    //Error states
    #define ERRORIDENTIFIER 501
    #define ERRORFLOAT 502
    #define ERRORFLOATSCI 503
    #define ERRORCHAR 504
    #define ERROROR 505
    #define ERRORAND 506
    #define ERRORUNKNOWN 599

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

void Parser::step() {
    for (Symbol s: Symbol::derive(hash(token.grammeme))) {
        symbols.push_back(s);
    }
}

void Parser::transduce(std::string &text) {
    symbols.push_back(Symbol(PROGRAM));
    // Look through the entire text
    for (int i = 0; i < text.length(); i++) {
        token = lexer->generateToken(i, text);
        if (IS_ERROR(token)) {
            // Lexical error
        }
        if (COMPARE(symbols.back(), token)) {
            symbols.pop_back();
        } else if (isValidDerivation()) {
            symbols.pop_back();
            step();
        } else {
            // Syntactical error
        }
    }
}

int Parser::hash(int grammeme) {
    switch (grammeme) {
        case RESERVED:
            std::string reserved = token.lexeme;
            if (reserved == "class") {
                return 0;
            } else if () {

            }
        case IDENTIFIER:

        case COMMENTARY:

        case INTEGER:

        case FLOAT:

        case FLOATSCI:

        case CHARACTER:

        case STRING:

        case TIMES_SIGN:

        case OVER_SIGN:

        case PLUS_SIGN:

        case MINUS_SIGN:

        case MODULO:

        case OR:

        case AND:

        case NOT:

        case LESSTHAN:

        case LESSEQUALS:

        case GREATERTHAN:

        case GREATEREQUALS:

        case EQUALS:

        case NEQUALS:

        case EQUAL_SIGN:

        case POINT:

        case COMMA:

        case COLON:

        case SEMICOLON:

        case PARENTHESISOPEN:

        case PARENTHESISCLOSE:

        case BRACKETSOPEN:

        case BRACKETSCLOSE:

        case SQUAREBOPEN:

        case SQUAREBCLOSE:

        default:
    }
}
