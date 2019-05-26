#include "symbol.h"

Symbol::Symbol(int g) {
    grammeme = g;
}

static std::list<Symbol> Symbol::derive(int production) {
    list<Symbol> symbols();
    switch (production) {
        case EXPRESSION:
            symbols
        default:
    }
    return symbols;
}