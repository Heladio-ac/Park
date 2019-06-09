#include "parser.h"
#include "lexer.h"
#include "symbol.h"
#include "token.h"

#include "tree_util.hh"

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
    {2,   602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 1,   602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602, 602},
    {603, 603, 4,   3,   603, 603, 603, 603, 603, 603, 4,   603, 603, 603, 4,   603, 603, 4,   603, 603, 603, 603, 603, 4,   4,   4,   603, 4,   603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603, 603},
    {604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 5,   604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604, 604},
    {605, 605, 605, 605, 7,   605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 605, 6,   605, 605, 605, 605, 605, 605, 605, 605},
    {606, 606, 606, 606, 606, 8,   9,   10,  11,  12,  606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606, 606},
    {607, 607, 14,  607, 607, 607, 607, 607, 607, 607, 13,  14,  607, 14,  13,  607, 14,  13,  14,  607, 607, 607, 607, 13,  13,  13,  607, 13,  607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607, 607},
    {608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 16,  608, 608, 608, 18,  608, 608, 17,  608, 608, 608, 608, 608, 19,  20,  21,  608, 15,  608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608, 608},
    {609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 22,  609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609, 609},
    {610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 23,  610, 610, 23,  23,  23,  23,  23,  610, 610, 610, 610, 610, 610, 610, 23,  610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 610, 23,  610, 610, 610, 610, 610},
    {611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 24,  611, 611, 611, 611, 611, 611, 611, 611, 611, 611, 25,  611, 25,  611, 25,  611, 611, 611, 611},
    {612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 26,  612, 612, 26,  26,  26,  26,  26,  612, 612, 612, 612, 612, 612, 612, 26,  612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 612, 26,  612, 612, 612, 612, 612},
    {613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 613, 27,  613, 613, 613, 613, 613, 613, 613, 613, 613, 28,  613, 28,  613, 28,  613, 613, 613, 613},
    {614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 29,  614, 614, 29,  29,  29,  29,  29,  614, 614, 614, 614, 614, 614, 614, 29,  614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 614, 29,  614, 614, 614, 614, 614},
    {615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 31,  615, 615, 31,  31,  31,  31,  31,  615, 615, 615, 615, 615, 615, 615, 30,  615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 615, 31,  615, 615, 615, 615, 615},
    {616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 32,  616, 616, 32,  32,  32,  32,  32,  616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 616, 32,  616, 616, 616, 616, 616},
    {617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 617, 34,  34,  617, 33,  33,  33,  33,  33,  33,  617, 617, 34,  617, 34,  617, 34,  617, 617, 617, 617},
    {618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 37,  38,  39,  40,  35,  36,  618, 618, 618, 618, 618, 618, 618, 618, 618, 618, 618},
    {619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 41,  619, 619, 41,  41,  41,  41,  41,  619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 619, 41,  619, 619, 619, 619, 619},
    {620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 620, 42,  43,  620, 44,  44,  620, 44,  44,  44,  44,  44,  44,  620, 620, 44,  620, 44,  620, 44,  620, 620, 620, 620},
    {621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 45,  621, 621, 45,  45,  45,  45,  45,  621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 621, 45,  621, 621, 621, 621, 621},
    {622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 622, 46,  47,  49,  49,  48,  49,  49,  622, 49,  49,  49,  49,  49,  49,  622, 622, 49,  622, 49,  622, 49,  622, 622, 622, 622},
    {623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 50,  623, 623, 51,  52,  53,  54,  55,  623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 623, 56,  623, 623, 623, 623, 623},
    {624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 57,  624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624, 624},
    {625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 58,  625, 59,  625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625, 625},
    {626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 60,  626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626, 626},
    {627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 61,  627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627, 627},
    {628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 62,  628, 628, 62,  62,  62,  62,  62,  628, 628, 628, 628, 628, 628, 628, 62,  628, 628, 628, 628, 628, 628, 628, 628, 628, 628, 628,  62, 628, 628, 628, 628, 628},
    {629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 629, 63,  629, 629, 629, 64,  629, 629, 629, 629},
    {630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 65,  630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630, 630},
    {631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 66,  631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631, 631},
    {632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 67,  632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632, 632}
};

bool compare(Symbol, Token);
std::string getError(int);

Parser::Parser() {
    lexer = new Lexer();
}

void Parser::step() {
    Symbol top = symbols.back();
    int column = Symbol::hash(token.grammeme, token.lexeme);
    int row = top.grammeme;
    int production = prediction[row][column];
    symbols.pop_back();
    std::list<Symbol> productions = Symbol::derive(production);
    tree<std::string>::iterator loc = syntaxTree.begin();
    tree<std::string>::iterator end = syntaxTree.end();
    do {
        loc = std::find(++loc, end, top.getGrammeme());
    } while (loc != end && loc.number_of_children());
    if (productions.empty()) {
        syntaxTree.append_child(loc, "ε");
    } else {
        for (Symbol s: productions) {
            symbols.push_back(s);
        }
        productions.reverse();
        for (Symbol s: productions) {
            syntaxTree.append_child(loc, s.getGrammeme());
        }
    }
}

bool Parser::transduce(std::string &text) {
    restart();
    Symbol program = Symbol(PROGRAM, false);
    Token eof = Token("$", END_OF_FILE);
    syntaxTree.insert(syntaxTree.begin(), program.getGrammeme());
    syntaxTree.insert(syntaxTree.begin(), eof.getGrammeme());
    symbols.push_back(eof);
    symbols.push_back(program);
    // Look through the entire text
    bool next = false;
    Symbol top;
    int production, column, row;
    for (unsigned int i = 0; i < text.length(); i++) {
        token = lexer->generateToken(i, text);
        next = false;
        while (!next) {
            top = symbols.back();
            if (IS_ERROR(token)) {
                // Lexical error
                error = "Lexical error: " + token.getGrammeme();
                return false;
            } else if (compare(top, token)) {
                symbols.pop_back();
                next = true;
            } else if (symbols.back().terminal) {
                // Syntactical error
                error = "Syntactical error, non matching terminal\n";
                error += "Expected \"" + symbols.back().getGrammeme() + "\", but found \"" + token.getGrammeme() + "\"";
                return false;
            } else {
                column = Symbol::hash(token.grammeme, token.lexeme);
                row = symbols.back().grammeme;
                production = prediction[row][column];
                if (production < 600) {
                    step();
                } else {
                    // Syntactical error
                    error = "Syntactical error, not valid derivation:\n" + getError(production);
                    return false;
                }
            }
        }
    }
    if (symbols.empty()) return true;
    else return false;
}

void Parser::restart() {
    lexer->restart();
    symbols.clear();
    syntaxTree.clear();
}

bool compare(Symbol symbol, Token token) {
    if (symbol.terminal) {
        return symbol.grammeme == Symbol::hash(token.grammeme, token.lexeme);
    } else {
        return false;
    }
}

std::string getError(int error) {
    switch (error) {
        case 601:
            return "Program’s head: The program must start with either library declaration or class definition";
        case 602:
            return "Program’s head: Expected class definition or the import of a library";
        case 603:
            return "Expected variable declaration or a valid statement";
        case 604:
            return "Variables: Expected a variable identifier";
        case 605:
            return "Variables declaration: Expected a , or the “as” reserved word";
        case 606:
            return "Type specification: Invalid type";
        case 607:
            return "Expected a valid statement or the “end” reserved word";
        case 608:
            return "Statement: Invalid start of statement";
        case 609:
            return "Assignment: Invalid start of assignment statement";
        case 610:
            return "Expression: Invalid start of expression";
        case 611:
            return "Expression: Invalid expression, expected a delimiter or a logical disjunction";
        case 612:
            return "Expression: Invalid start of expression";
        case 613:
            return "Expression: Invalid expression, expected a delimiter or a logical operation";
        case 614:
            return "Expression: Invalid start of expression";
        case 615:
            return "Expression: Invalid expression, expected a delimiter or a logical negation";
        case 616:
            return "Expression: Invalid start of expression";
        case 617:
            return "Expression: Invalid expression, expected a delimiter, a logical operation or a relational operator";
        case 618:
            return "Expression: Invalid expression, expected a relational operator";
        case 619:
            return "Expression: Invalid start of expression";
        case 620:
            return "Expression: Invalid expression, expected a delimiter, a logical operation, a relational operator or an arithmetic addition";
        case 621:
            return "Expression: Invalid start of expression";
        case 622:
            return "Expression: Invalid expression, expected a delimiter, a logical operation, a relational operator or an arithmetic operation";
        case 623:
            return "Expression: Invalid start of expression";
        case 624:
            return "If statement: Expected the reserved word “if”";
        case 625:
            return "If statement: Expected the reserved word “else” or “endif”";
        case 626:
            return "While loop: Expected the reserved word “while”";
        case 627:
            return "For loop: Expected the reserved word “while”";
        case 628:
            return "Expressions: Invalid start of expression";
        case 629:
            return "Expressions: Invalid expressions, expected a , or a closing parenthesis";
        case 630:
            return "Read instruction: Expected the reserved word “read”";
        case 631:
            return "Write instruction: Expected the reserved word “write”";
        case 632:
            return "Enter statement: Expected the reserved word “enter”";
        default:
            return "Unknown error";
    }
}
