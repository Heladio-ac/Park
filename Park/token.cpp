#include "token.h"

// Delimiting states
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
