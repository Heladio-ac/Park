#include "symbol.h"

#include <iostream>

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

Symbol::Symbol(int g, bool t) {
    grammeme = g;
    terminal = t;
}

Symbol::Symbol() {}

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
        case END_OF_FILE:
            return -1;
        default:
            return 699;
    }
}

std::list<Symbol> Symbol::derive(int production) {
    std::list<Symbol> symbols;
    switch (production) {
        case 0:
            symbols.push_front(Symbol(DECL_LIBRARIES, false));
            symbols.push_front(Symbol(hash(RESERVED, "class"), true));
            symbols.push_front(Symbol(hash(IDENTIFIER, ""), true));
            symbols.push_front(Symbol(hash(RESERVED, "begin"), true));
            symbols.push_front(Symbol(DECL_VARIABLES, false));
            symbols.push_front(Symbol(STATEMENTS, false));
            symbols.push_front(Symbol(hash(RESERVED, "end"), true));
        break;
        case 1:
            symbols.push_front(Symbol(hash(RESERVED, "import"), true));
            symbols.push_front(Symbol(hash(LIBRARY, ""), true));
            symbols.push_front(Symbol(hash(SEMICOLON, ";"), true));
            symbols.push_front(Symbol(DECL_LIBRARIES, false));
        break;
        case 3:
            symbols.push_front(Symbol(hash(RESERVED, "def"), true));
            symbols.push_front(Symbol(VARIABLES, false));
            symbols.push_front(Symbol(hash(RESERVED, "as"), true));
            symbols.push_front(Symbol(TYPE, false));
            symbols.push_front(Symbol(hash(SEMICOLON, ";"), true));
            symbols.push_front(Symbol(DECL_VARIABLES, false));
        break;
        case 5:
            symbols.push_front(Symbol(hash(IDENTIFIER, ""), true));
            symbols.push_front(Symbol(MORE_VARIABLES, false));
        break;
        case 6:
            symbols.push_front(Symbol(hash(COMMA, ","), true));
            symbols.push_front(Symbol(VARIABLES, false));
        break;
        case 8:
            symbols.push_front(Symbol(hash(RESERVED, "integer"), true));
        break;
        case 9:
            symbols.push_front(Symbol(hash(RESERVED, "float"), true));
        break;
        case 10:
            symbols.push_front(Symbol(hash(RESERVED, "char"), true));
        break;
        case 11:
            symbols.push_front(Symbol(hash(RESERVED, "string"), true));
        break;
        case 12:
            symbols.push_front(Symbol(hash(RESERVED, "boolean"), true));
        break;
        case 13:
            symbols.push_front(Symbol(STATEMENT, false));
            symbols.push_front(Symbol(hash(SEMICOLON, ";"), true));
            symbols.push_front(Symbol(STATEMENTS, false));
        break;
        case 15:
            symbols.push_front(Symbol(ASSIGNMENT, false));
        break;
        case 16:
            symbols.push_front(Symbol(IF, false));
        break;
        case 17:
            symbols.push_front(Symbol(WHILE, false));
        break;
        case 18:
            symbols.push_front(Symbol(FOR, false));
        break;
        case 19:
            symbols.push_front(Symbol(READ, false));
        break;
        case 20:
            symbols.push_front(Symbol(WRITE, false));
        break;
        case 21:
            symbols.push_front(Symbol(ENTER, false));
        break;
        case 22:
            symbols.push_front(Symbol(hash(IDENTIFIER, ""), true));
            symbols.push_front(Symbol(hash(EQUAL_SIGN, "="), true));
            symbols.push_front(Symbol(EXPRESSION_0, false));
        break;
        case 23:
            symbols.push_front(Symbol(EXPRESSION_1, false));
            symbols.push_front(Symbol(DISJUNCTION, false));
        break;
        case 24:
            symbols.push_front(Symbol(hash(OR, "||"), true));
            symbols.push_front(Symbol(EXPRESSION_0, false));
        break;
        case 26:
            symbols.push_front(Symbol(EXPRESSION_2, false));
            symbols.push_front(Symbol(CONJUNCTION, false));
        break;
        case 27:
            symbols.push_front(Symbol(hash(AND, "&&"), true));
            symbols.push_front(Symbol(EXPRESSION_1, false));
        break;
        case 29:
            symbols.push_front(Symbol(NEGATION, false));
            symbols.push_front(Symbol(EXPRESSION_3, false));
        break;
        case 30:
            symbols.push_front(Symbol(hash(NOT, "!"), true));
        break;
        case 32:
            symbols.push_front(Symbol(EXPRESSION_4, false));
            symbols.push_front(Symbol(COMPARISON, false));
        break;
        case 33:
            symbols.push_front(Symbol(RELATIONAL_OPERATOR, false));
            symbols.push_front(Symbol(EXPRESSION_4, false));
        break;
        case 35:
            symbols.push_front(Symbol(hash(EQUALS, "=="), true));
        break;
        case 36:
            symbols.push_front(Symbol(hash(NEQUALS, "!="), true));
        break;
        case 37:
            symbols.push_front(Symbol(hash(LESSTHAN, "<"), true));
        break;
        case 38:
            symbols.push_front(Symbol(hash(LESSEQUALS, "<="), true));
        break;
        case 39:
            symbols.push_front(Symbol(hash(GREATERTHAN, ">"), true));
        break;
        case 40:
            symbols.push_front(Symbol(hash(GREATEREQUALS, ">="), true));
        break;
        case 41:
            symbols.push_front(Symbol(ADDEND, false));
            symbols.push_front(Symbol(ADDITION, false));
        break;
        case 42:
            symbols.push_front(Symbol(hash(PLUS_SIGN, "+"), true));
            symbols.push_front(Symbol(EXPRESSION_4, false));
        break;
        case 43:
            symbols.push_front(Symbol(hash(MINUS_SIGN, "-"), true));
            symbols.push_front(Symbol(EXPRESSION_4, false));
        break;
        case 45:
            symbols.push_front(Symbol(FACTOR, false));
            symbols.push_front(Symbol(MULTIPLICATION, false));
        break;
        case 46:
            symbols.push_front(Symbol(hash(TIMES_SIGN, "*"), true));
            symbols.push_front(Symbol(ADDEND, false));
        break;
        case 47:
            symbols.push_front(Symbol(hash(OVER_SIGN, "/"), true));
            symbols.push_front(Symbol(ADDEND, false));
        break;
        case 48:
            symbols.push_front(Symbol(hash(MODULO, "%"), true));
            symbols.push_front(Symbol(ADDEND, false));
        break;
        case 50:
            symbols.push_front(Symbol(hash(IDENTIFIER, ""), true));
        break;
        case 51:
            symbols.push_front(Symbol(hash(INTEGER, ""), true));
        break;
        case 52:
            symbols.push_front(Symbol(hash(FLOAT, ""), true));
        break;
        case 53:
            symbols.push_front(Symbol(hash(FLOATSCI, ""), true));
        break;
        case 54:
            symbols.push_front(Symbol(hash(CHARACTER, ""), true));
        break;
        case 55:
            symbols.push_front(Symbol(hash(STRING, ""), true));
        break;
        case 56:
            symbols.push_front(Symbol(hash(PARENTHESISOPEN, "("), true));
            symbols.push_front(Symbol(EXPRESSION_0, false));
            symbols.push_front(Symbol(hash(PARENTHESISCLOSE, ")"), true));
        break;
        case 57:
            symbols.push_front(Symbol(hash(RESERVED, "if"), true));
            symbols.push_front(Symbol(hash(PARENTHESISOPEN, "("), true));
            symbols.push_front(Symbol(EXPRESSION_0, false));
            symbols.push_front(Symbol(hash(PARENTHESISCLOSE, ")"), true));
            symbols.push_front(Symbol(STATEMENTS, false));
            symbols.push_front(Symbol(ELSE, false));
            symbols.push_front(Symbol(hash(RESERVED, "endif"), true));
        break;
        case 58:
            symbols.push_front(Symbol(hash(RESERVED, "else"), true));
            symbols.push_front(Symbol(STATEMENTS, false));
        break;
        case 60:
            symbols.push_front(Symbol(hash(RESERVED, "while"), true));
            symbols.push_front(Symbol(hash(PARENTHESISOPEN, "("), true));
            symbols.push_front(Symbol(EXPRESSION_0, false));
            symbols.push_front(Symbol(hash(PARENTHESISCLOSE, ")"), true));
            symbols.push_front(Symbol(STATEMENTS, false));
            symbols.push_front(Symbol(hash(RESERVED, "endwhile"), true));
        break;
        case 61:
            symbols.push_front(Symbol(hash(RESERVED, "for"), true));
            symbols.push_front(Symbol(hash(PARENTHESISOPEN, "("), true));
            symbols.push_front(Symbol(ASSIGNMENT, false));
            symbols.push_front(Symbol(hash(COLON, ":"), true));
            symbols.push_front(Symbol(EXPRESSION_0, false));
            symbols.push_front(Symbol(hash(PARENTHESISCLOSE, ")"), true));
            symbols.push_front(Symbol(STATEMENTS, false));
            symbols.push_front(Symbol(hash(RESERVED, "endfor"), true));
        break;
        case 62:
            symbols.push_front(Symbol(EXPRESSION_0, false));
            symbols.push_front(Symbol(MORE_EXPRESSIONS, false));
        break;
        case 63:
            symbols.push_front(Symbol(hash(COMMA, ","), true));
            symbols.push_front(Symbol(EXPRESSIONS, false));
        break;
        case 65:
            symbols.push_front(Symbol(hash(RESERVED, "read"), true));
            symbols.push_front(Symbol(hash(PARENTHESISOPEN, "("), true));
            symbols.push_front(Symbol(EXPRESSIONS, false));
            symbols.push_front(Symbol(hash(PARENTHESISCLOSE, ")"), true));
        break;
        case 66:
            symbols.push_front(Symbol(hash(RESERVED, "write"), true));
            symbols.push_front(Symbol(hash(PARENTHESISOPEN, "("), true));
            symbols.push_front(Symbol(EXPRESSIONS, false));
            symbols.push_front(Symbol(hash(PARENTHESISCLOSE, ")"), true));
        break;
        case 67:
            symbols.push_front(Symbol(hash(RESERVED, "enter"), true));
        break;
        case 2: case 4: case 7: case 14: case 25:
        case 28: case 31: case 34: case 44:
        case 49: case 59: case 64:
        break;
    }
    return symbols;
}

std::string Symbol::getGrammeme() {
    std::cout << "Getting grammeme" << std::endl;
    std::cout << "Grammeme: " + std::to_string(grammeme) << std::endl;
    if (terminal) {
        switch (grammeme) {
            case 0:
                return "class";
            case 1:
                return "begin";
            case 2:
                return "end";
            case 3:
                return "def";
            case 4:
                return "as";
            case 5:
                return "integer";
            case 6:
                return "float";
            case 7:
                return "char";
            case 8:
                return "string";
            case 9:
                return "boolean";
            case 10:
                return "if";
            case 11:
                return "else";
            case 12:
                return "elseif";
            case 13:
                return "endif";
            case 14:
                return "for";
            case 15:
                return "do";
            case 16:
                return "endfor";
            case 17:
                return "while";
            case 18:
                return "endwhile";
            case 19:
                return "function";
            case 20:
                return "endfunction";
            case 21:
                return "import";
            case 22:
                return "null";
            case 23:
                return "read";
            case 24:
                return "write";
            case 25:
                return "enter";
            case 26:
                return "principal";
            case 27:
                return "Identifier";
            case 28:
                return "Library identifier";
            case 29:
                return "Commentary";
            case 30:
                return "Integer constant";
            case 31:
                return "Floating point constant";
            case 32:
                return "Floating point constant with scientific notation";
            case 33:
                return "Character constant";
            case 34:
                return "String constant";
            case 35:
                return "*";
            case 36:
                return "/";
            case 37:
                return "+";
            case 38:
                return "-";
            case 39:
                return "%";
            case 40:
                return "OR";
            case 41:
                return "AND";
            case 42:
                return "NOT";
            case 43:
                return "<";
            case 44:
                return "<=";
            case 45:
                return ">";
            case 46:
                return ">=";
            case 47:
                return "==";
            case 48:
                return "!=";
            case 49:
                return "=";
            case 50:
                return ".";
            case 51:
                return ",";
            case 52:
                return ":";
            case 53:
                return ";";
            case 54:
                return "(";
            case 55:
                return ")";
            case 56:
                return "{";
            case 57:
                return "}";
            case 58:
                return "[";
            case 59:
                return "]";
            case -1:
                return "EOF";
            case ERRORIDENTIFIER:
                return "Identifiers can not end with a _";
            case ERRORLIBRARY:
                return "Library identifiers must end with \".lye\"";
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
    } else {
        switch (grammeme) {
            case PROGRAM:
                return "Program";
            case DECL_LIBRARIES:
                return "Libraries declaration";
            case DECL_VARIABLES:
                return "Variables declaration";
            case VARIABLES:
                return "Variables";
            case MORE_VARIABLES:
                return "More variables";
            case TYPE:
                return "Variable type";
            case STATEMENTS:
                return "Statements";
            case STATEMENT:
                return "Statement";
            case ASSIGNMENT:
                return "Assignment";
            case EXPRESSION_0:
                return "Zeroth order expression";
            case DISJUNCTION:
                return "Logical disjunction";
            case EXPRESSION_1:
                return "First order expression";
            case CONJUNCTION:
                return "Logical conjunction";
            case EXPRESSION_2:
                return "Second order expression";
            case NEGATION:
                return "Logical negation";
            case EXPRESSION_3:
                return "Third order expression";
            case COMPARISON:
                return "Comparison";
            case RELATIONAL_OPERATOR:
                return "Relational operator";
            case EXPRESSION_4:
                return "Fourth order expression";
            case ADDITION:
                return "Arithmetical addition";
            case ADDEND:
                return "Addend expression";
            case MULTIPLICATION:
                return "Arithmetical multiplication";
            case FACTOR:
                return "Factor expression";
            case IF:
                return "IF statement";
            case ELSE:
                return "ELSE clause";
            case WHILE:
                return "WHILE loop";
            case FOR:
                return "FOR loop";
            case EXPRESSIONS:
                return "Expressions";
            case MORE_EXPRESSIONS:
                return "More expressions";
            case READ:
                return "READ instruction";
            case WRITE:
                return "WRITE instruction";
            case ENTER:
                return "Enter";
            default:
                return "Unknown symbol";
        }
    }
}
