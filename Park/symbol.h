#ifndef SYMBOL_H
#define SYMBOL_H

#include <list>

class Symbol {
    public:
        static std::list<Symbol> derive(Symbol);
};

#endif
