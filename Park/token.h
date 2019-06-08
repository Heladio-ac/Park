#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "symbol.h"

class Symbol;
class Token : public Symbol {
public:
    std::string lexeme;

    Token(void);
    Token(std::string l, int g);
    std::string getGrammeme(void);
};
#endif
