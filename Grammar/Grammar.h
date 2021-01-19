//
// Created by 胡凌瑞 on 2021/1/16.
//

#ifndef REGULAR_EXPRESSION_ENGINE_GRAMMAR_H
#define REGULAR_EXPRESSION_ENGINE_GRAMMAR_H
#include "Symbol.h"
#include "vector"
#include "Production.h"
#include "map"
#include <set>

class Grammar {
private:
    Symbol* startSymbol;
    std::vector<Production*> productions;
    std::map<Symbol*, std::set<Symbol*>> FIRST;
    


public:
    void addProduction(Production* p) {
        productions.push_back(p);
    }

    void assignStartSymbol(Production* p) {
        startSymbol = p->getStart();
    }
};

#endif //REGULAR_EXPRESSION_ENGINE_GRAMMAR_H
