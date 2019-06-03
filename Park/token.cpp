#include "token.h"

// Delimiting states
#ifndef TERMINAL_SYMBOLS
#define TERMINAL_SYMBOLS
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

Token::Token(std::string l, int g) : Symbol(g){
    lexeme = l;
    grammeme = g;
}

std::string Token::getGrammeme() {
    switch (grammeme) {
        // Accepted
        case RESERVED:
            return "Reserved word";
        case IDENTIFIER:
            return "Identifier";
        case LIBRARY:
            return "Library identifier";
        case COMMENTARY:
            return "Commentary";
        case INTEGER:
            return "Integer";
        case FLOAT:
            return "Real number";
        case FLOATSCI:
            return "Real number w/exponent";
        case CHARACTER:
            return "Character";
        case STRING:
            return "String";
        case TIMES_SIGN:
            return "Multiplication";
        case OVER_SIGN:
            return "Division";
        case PLUS_SIGN:
            return "Addition";
        case MINUS_SIGN:
            return "Substraction";
        case MODULO:
            return "Modulo";
        case OR:
            return "Logical OR";
        case AND:
            return "Logical AND";
        case NOT:
            return "Logical NOT";
        case LESSTHAN:
            return "Less than";
        case LESSEQUALS:
            return "Less than or equals";
        case GREATERTHAN:
            return "Greater than";
        case GREATEREQUALS:
            return "Greater than or equals";
        case EQUALS:
            return "Equals";
        case NEQUALS:
            return "Is different";
        case EQUAL_SIGN:
            return "Assign";
        case POINT:
            return "Point";
        case COMMA:
            return "Comma";
        case COLON:
            return "Colon";
        case SEMICOLON:
            return "Semi-colon";
        case PARENTHESISOPEN:
            return "Open Parenthesis";
        case PARENTHESISCLOSE:
            return "Close Parenthesis";
        case BRACKETSOPEN:
            return "Open Brackets";
        case BRACKETSCLOSE:
            return "Close Brackets";
        case SQUAREBOPEN:
            return "Open Square Brackets";
        case SQUAREBCLOSE:
            return "Close Square Brackets";
        // Errors
        case ERRORIDENTIFIER:
            return "Identifiers can not end with a _";
        case ERRORLIBRARY:
            return "Library identifiers must end with 'lye'";
        case ERRORFLOAT:
            return "Malformed floating point constant, expected a digit after the point";
        case ERRORFLOATSCI:
            return "Malformed floating point constant, expected a digit or +/- sign after the exponent";
        case ERRORCHAR:
            return "Malformed character constant, expected a closing apostrophe";
        case ERROROR:
            return "Malformed OR operator, expected a second |";
        case ERRORAND:
            return "Malformed AND operator, expected a second &";
        case ERRORUNKNOWN: default:
            return "Unknown Error";
    }
}
