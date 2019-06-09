#include "lexer.h"

#include <iostream>

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
    #define ASSIGNMENT 124
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

// Symbols sets
#ifndef SYMBOLS
#define SYMBOLS
    #define LOWERL 4
    #define UPPERL 5
    #define DIGITS 6
    #define BLANKS 16
    #define ELSE 32
#endif

// Functions
#ifndef LEXER_FUNC
#define LEXER_FUNC
    #define IS_VALID !(state >= 500)
    #define IS_DELIMITER (state >= 100)
#endif

static int transition[37][33] = {
    {2,   1,   1,   1,   1,   2,   10,  599, 19,  7,   20,  21,  22,  35,  16,  18,  0,   23,  25,  27,  28,  30,  34,  36,  126, 128, 129, 130, 131, 132, 133, 134, 599},
    {2,   1,   1,   1,   1,   2,   2,   3,   101, 101, 101, 101, 101, 4,   101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101},
    {2,   2,   2,   2,   2,   2,   2,   3,   102, 102, 102, 102, 102, 4,   102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102},
    {2,   2,   2,   2,   2,   2,   2,   501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501, 501},
    {502, 502, 5,   502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502},
    {502, 502, 502, 6,   502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502},
    {502, 103, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502, 502},
    {111, 111, 111, 111, 111, 111, 111, 111, 8,   111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111},
    {8,   8,   6,   7,   8,   8,   8,   8,   9,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8},
    {8,   8,   6,   7,   8,   8,   8,   8,   9,   104, 8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8,   8},
    {105, 105, 105, 105, 105, 105, 10,  105, 105, 105, 105, 105, 105, 11,  105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105},
    {503, 503, 503, 503, 503, 503, 12,  503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503, 503},
    {13,  13,  106, 106, 106, 106, 12,  106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106},
    {504, 504, 504, 504, 504, 504, 15,  504, 504, 504, 14,  14,  504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504},
    {504, 504, 504, 504, 504, 504, 15,  504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504, 504},
    {107, 107, 107, 107, 107, 107, 15,  107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107},
    {17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  108, 17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17,  17},
    {505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 108, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505, 505},
    {18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  109, 18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18,  18},
    {110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110},
    {112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112},
    {113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113},
    {114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114},
    {506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 24,  506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506, 506},
    {115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115},
    {507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 26,  507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507, 507},
    {116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116},
    {117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 33,  117, 117, 117, 117, 117, 117, 117, 117, 117, 117},
    {118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 29,  118, 118, 118, 118, 118, 118, 118, 118, 118, 118},
    {119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119},
    {120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 31,  120, 120, 120, 120, 120, 120, 120, 120, 120, 120},
    {121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121},
    {122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122},
    {123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123},
    {124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 32,  124, 124, 124, 124, 124, 124, 124, 124, 124, 124},
    {125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125},
    {127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127}
};

static std::string reservedWords[] = {
    "class",
    "begin",
    "end",
    "def",
    "as",
    "integer",
    "float",
    "char",
    "string",
    "boolean",
    "if",
    "else",
    "elseif",
    "endif",
    "for",
    "do",
    "endfor",
    "while",
    "endwhile",
    "function",
    "endfunction",
    "import",
    "null",
    "read",
    "write",
    "enter",
    "principal"
};

bool isReserved(std::string);

Lexer::Lexer(void) {
    state = 0;
    lexeme = "";
}

void Lexer::step(char symbol) {
    state = transition[state][hash(symbol)];
}

Token Lexer::generateToken(unsigned int &index, std::string &text) {
    restart();
    while (true) {
        step(text[index]);
        if (IS_DELIMITER) break;
        if (state) {
            lexeme += text[index];
        }
        index++;
        std::cout << index << std::endl;
    }
    if (index == text.length()) {
        return Token("EOF", -1);
    }
    if (isFinal()) {
        lexeme += text[index];
    } else {
        index--;
    }
    if (IS_VALID && state == RESERVED) {
        state = (isReserved(lexeme) ? RESERVED : IDENTIFIER);
    }
    return Token(lexeme, state);
}

int Lexer::hash(char symbol) {
    if (symbol == 'E') {
        return 0;
    } else if (symbol == 'e') {
        return 1;
    } else if (symbol == 'l') {
        return 2;
    } else if (symbol == 'y') {
        return 3;
    } else if (islower(symbol)) {
        return LOWERL;
    } else if (isupper(symbol)) {
        return UPPERL;
    } else if (isdigit(symbol)) {
        return DIGITS;
    } else if (symbol == '_') {
        return 7;
    } else if (symbol == '*') {
        return 8;
    } else if (symbol == '/') {
        return 9;
    } else if (symbol == '+') {
        return 10;
    } else if (symbol == '-') {
        return 11;
    } else if (symbol == '%') {
        return 12;
    } else if (symbol == '.') {
        return 13;
    } else if (symbol == '\'') {
        return 14;
    } else if (symbol == '\"') {
        return 15;
    } else if (symbol == ' ' || symbol == '\n' || symbol == '\t') {
        return BLANKS;
    } else if (symbol == '|') {
        return 17;
    } else if (symbol == '&') {
        return 18;
    } else if (symbol == '!') {
        return 19;
    } else if (symbol == '<') {
        return 20;
    } else if (symbol == '>') {
        return 21;
    } else if (symbol == '=') {
        return 22;
    } else if (symbol == ':') {
        return 23;
    } else if (symbol == ',') {
        return 24;
    } else if (symbol == ';') {
        return 25;
    } else if (symbol == '(') {
        return 26;
    } else if (symbol == ')') {
        return 27;
    } else if (symbol == '{') {
        return 28;
    } else if (symbol == '}') {
        return 29;
    } else if (symbol == '[') {
        return 30;
    } else if (symbol == ']') {
        return 31;
    } else {
        return ELSE;
    }
}

void Lexer::restart() {
    state = 0;
    lexeme = "";
}

bool Lexer::isFinal() {
    switch (state) {
        case LIBRARY: case COMMENTARY:
        case CHARACTER: case STRING:
        case COMMA: case SEMICOLON:
        case PARENTHESISOPEN: case PARENTHESISCLOSE:
        case BRACKETSOPEN: case BRACKETSCLOSE:
        case SQUAREBOPEN: case SQUAREBCLOSE:
        case ERRORUNKNOWN:
            return true;
        default:
            return false;
    }
}

bool isReserved(std::string lexeme) {
    for (std::string reserved: reservedWords) {
        if (reserved == lexeme) {
            return true;
        }
    }
    return false;
}
