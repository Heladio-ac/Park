#ifndef SYMBOL_H
#define SYMBOL_H

#include <list>
#include <string>

class Symbol {
    public:
        int grammeme;
        bool terminal;

        Symbol(int, bool);
        static std::list<Symbol> derive(int);
        static int hash(int, std::string);
};

#endif
