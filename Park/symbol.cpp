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

Symbol::Symbol(int g, bool t) {
    grammeme = g;
    terminal = t;
}

int Symbol::hash(int grammeme, std::string lexeme) {
    switch (grammeme) {
        case RESERVED:
            if (lexeme == "class") {
                return 0;
            } else if (lexeme == "begin") {
                return 1;
            } else if (lexeme == "end") {
                return 2;
            } else if (lexeme == "def") {
                return 3;
            } else if (lexeme == "as") {
                return 4;
            } else if (lexeme == "integer") {
                return 5;
            } else if (lexeme == "float") {
                return 6;
            } else if (lexeme == "char") {
                return 7;
            } else if (lexeme == "string") {
                return 8;
            } else if (lexeme == "boolean") {
                return 9;
            } else if (lexeme == "if") {
                return 10;
            } else if (lexeme == "else") {
                return 11;
            } else if (lexeme == "elseif") {
                return 12;
            } else if (lexeme == "endif") {
                return 13;
            } else if (lexeme == "for") {
                return 14;
            } else if (lexeme == "do") {
                return 15;
            } else if (lexeme == "endfor") {
                return 16;
            } else if (lexeme == "while") {
                return 17;
            } else if (lexeme == "endwhile") {
                return 18;
            } else if (lexeme == "function") {
                return 19;
            } else if (lexeme == "endfunction") {
                return 20;
            } else if (lexeme == "import") {
                return 21;
            } else if (lexeme == "null") {
                return 22;
            } else if (lexeme == "read") {
                return 23;
            } else if (lexeme == "write") {
                return 24;
            } else if (lexeme == "enter") {
                return 25;
            } else if (lexeme == "principal") {
                return 26;
            } else {
                return 699;
            }
        case IDENTIFIER:
            return 27;
        case LIBRARY:
            return 28;
        case COMMENTARY:
            return 29;
        case INTEGER:
            return 30;
        case FLOAT:
            return 31;
        case FLOATSCI:
            return 32;
        case CHARACTER:
            return 33;
        case STRING:
            return 34;
        case TIMES_SIGN:
            return 35;
        case OVER_SIGN:
            return 36;
        case PLUS_SIGN:
            return 37;
        case MINUS_SIGN:
            return 38;
        case MODULO:
            return 39;
        case OR:
            return 40;
        case AND:
            return 41;
        case NOT:
            return 42;
        case LESSTHAN:
            return 43;
        case LESSEQUALS:
            return 44;
        case GREATERTHAN:
            return 45;
        case GREATEREQUALS:
            return 46;
        case EQUALS:
            return 47;
        case NEQUALS:
            return 48;
        case EQUAL_SIGN:
            return 49;
        case POINT:
            return 50;
        case COMMA:
            return 51;
        case COLON:
            return 52;
        case SEMICOLON:
            return 53;
        case PARENTHESISOPEN:
            return 54;
        case PARENTHESISCLOSE:
            return 55;
        case BRACKETSOPEN:
            return 56;
        case BRACKETSCLOSE:
            return 57;
        case SQUAREBOPEN:
            return 58;
        case SQUAREBCLOSE:
            return 59;
        default:
            return 699;
    }
}

std::list<Symbol> Symbol::derive(int production) {
    std::list<Symbol> symbols;
    switch (production) {
        case 0:
            symbols.push_back(Symbol(DECL_LIBRARIES, false));
            symbols.push_back(Symbol(hash(RESERVED, "class"), true));
            symbols.push_back(Symbol(hash(IDENTIFIER, ""), true));
            symbols.push_back(Symbol(hash(RESERVED, "begin"), true));
            symbols.push_back(Symbol(DECL_VARIABLES, false));
            symbols.push_back(Symbol(STATEMENTS, false));
            symbols.push_back(Symbol(hash(RESERVED, "end"), true));
        break;
        case 1:
            symbols.push_back(Symbol(hash(RESERVED, "import"), true));
            symbols.push_back(Symbol(LIBRARY, false));
            symbols.push_back(Symbol(hash(SEMICOLON, ""), true));
            symbols.push_back(Symbol(DECL_LIBRARIES, false));
        break;
        case 3:

        case 5:

        case 6:

        case 8:

        case 9:

        case 10:

        case 11:

        case 12:

        case 13:

        case 15:

        case 16:

        case 17:

        case 18:

        case 19:

        case 20:

        case 21:

        case 22:

        case 23:

        case 24:

        case 26:

        case 27:

        case 29:

        case 30:

        case 32:

        case 33:

        case 35:

        case 36:

        case 37:

        case 38:

        case 39:

        case 40:

        case 41:

        case 42:

        case 43:

        case 45:

        case 46:

        case 47:

        case 48:

        case 50:

        case 51:

        case 52:

        case 53:

        case 54:

        case 55:

        case 56:

        case 57:

        case 58:

        case 60:

        case 61:

        case 62:

        case 63:

        case 65:

        case 66:

        case 67:

        case 2: case 4: case 7: case 14: case 25:
        case 28: case 31: case 34: case 44:
        case 49: case 59: case 64:
        break;
    }
    return symbols;
}
