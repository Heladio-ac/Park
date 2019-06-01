#ifndef SYMBOL_H
#define SYMBOL_H

#include <list>

class Symbol {
    public:
        int grammeme;

        Symbol(int);
        static std::list<Symbol> derive(int);
};

#endif
