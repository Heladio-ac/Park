#ifndef ERROR_H
#define ERROR_H

#include <string>
#include "token.h"

class Error: public Token {

public:
    using Token::Token;
    std::string getError();
};

#endif // ERROR_H
