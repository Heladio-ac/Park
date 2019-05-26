#ifndef TOKEN_H
#define TOKEN_H

#include "symbol.h"

#include <string>

class Token : public Symbol{
public:
    std::string lexeme;

    Token(std::string l, int g);
    std::string getGrammeme();
};

#endif // TOKEN_H
