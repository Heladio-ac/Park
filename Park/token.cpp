#include "token.h"

Token::Token(std::string l, int g) : Symbol(g, true){
    lexeme = l;
    grammeme = g;
}

Token::Token() : Symbol() {}

std::string Token::getGrammeme() {
    grammeme = Symbol::hash(grammeme, lexeme);
    return Symbol::getGrammeme();
}
