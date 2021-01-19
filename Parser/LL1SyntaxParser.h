//
// Created by 胡凌瑞 on 2021/1/17.
//

#ifndef REGULAR_EXPRESSION_ENGINE_REGEXSYNTAXANALYZER_H
#define REGULAR_EXPRESSION_ENGINE_REGEXSYNTAXANALYZER_H

#include <utility>

#include "../Grammar/LL1Grammar.h"
#include "stack"

class RegexSyntaxAnalyzer {
private:
    std::vector<std::shared_ptr<Symbol>> regexSymbol;
    std::shared_ptr<Grammar> regexGrammar;
    std::map<std::shared_ptr<Symbol>, std::map<std::shared_ptr<Symbol>, std::shared_ptr<Production>>> M;

private:
    void computeBodyFIRST(std::shared_ptr<Production> p, std::set<std::shared_ptr<Symbol>> & set) {
        int bodiesSize = p->getBody().size();
        const auto& FIRST = regexGrammar->getFirst();
        const auto& FOLLOW = regexGrammar->getFollow();
        for(int i = 0; i < bodiesSize; ++i) {
            const auto& b = p->getBody()[i];
            if(b->getType() == Terminal) {
                set.insert(b);
                break;
            }
            if (b->getType() == Special) {
                set.insert(Symbol::epsilonSymbol);
                break;
            }
            if (b->getType() == Nonterminal) {
                const auto& s = FIRST.at(b);
                if(!s.count(Symbol::epsilonSymbol)) {
                    for(const auto& a : s)
                        set.insert(a);
                    break;
                }
                else if(s.count(Symbol::epsilonSymbol) && i != bodiesSize - 1) {
                    for(const auto& a : s) {
                        if(a != Symbol::epsilonSymbol)
                            set.insert(a);
                    }
                }
                else if(s.count(Symbol::epsilonSymbol) && i == bodiesSize - 1) {
                    for(const auto& a : s)
                        set.insert(a);
                }
            }
        }
    }

public:
    explicit RegexSyntaxAnalyzer(std::shared_ptr<Grammar> G) {
        regexGrammar = std::move(G);
    }

    RegexSyntaxAnalyzer(std::vector<std::shared_ptr<Symbol>> regexSymbol,
                        std::shared_ptr<Grammar> regexGrammar) : regexSymbol(std::move(regexSymbol)),
                                                                        regexGrammar(std::move(regexGrammar)) {}


    const std::map<std::shared_ptr<Symbol>, std::map<std::shared_ptr<Symbol>, std::shared_ptr<Production>>> &
    retrieveM() const {
        return M;
    }

public:
    void generatePredictiveParsingTable() {
        //获取语法中的生产式
        const auto& productions = regexGrammar->getProductions();

        //获取Symbol的FIRST和FOLLOW
        const auto& FIRST = regexGrammar->getFirst();
        const auto& FOLLOW = regexGrammar->getFollow();

        for(auto & p : productions) {
            const auto& bodies = p->getBody();
            const auto& A = p->getStart();
            int bodiesSize = bodies.size();
            //获取production的body的first集合
            std::set<std::shared_ptr<Symbol>> set;
            computeBodyFIRST(p, set);
            for(auto & a : set) {
                if(a->getType() == Terminal)
                    M[A][a] = p;
            }
            if(set.count(Symbol::epsilonSymbol)) {
                for(auto & a : FOLLOW.at(A))
                    M[A][a] = p;
            }
        }
    }

    void analyze() {
        //初始化步骤
        regexSymbol.push_back(Symbol::dollarSymbol);
        std::stack<std::shared_ptr<Symbol>> s;
        s.push(Symbol::dollarSymbol);
        s.push(regexGrammar->getStartSymbol());

        int ip = 0;
        auto X = s.top();
        auto a = regexSymbol[ip];

        while(X != Symbol::dollarSymbol) {
            if(X == a) {
                s.pop();
                std::cout<<"match: " << a->getSymbolName() << std::endl;
                ++ip;
                a = regexSymbol[ip];
            }
            else if (X->getType() == Terminal) {
                throw SyntaxError();
            }
            else if (!M.count(X) && !M[X].count(a)) {
                throw SyntaxError();
            }
            else if (M.count(X) && M[X].count(a)) {
                const auto production = M[X][a];
                std::cout<<production->show()<<std::endl;
                s.pop();
                const auto& productionBody = production->getBody();
                for(int i = (int)productionBody.size()-1; i >= 0; --i ) {
                    std::shared_ptr<Symbol> symbolToBePush = productionBody[i];
                    if(symbolToBePush != Symbol::epsilonSymbol) {
                        s.push(symbolToBePush);
                    }
                }
            }
            X = s.top();
        }
    }
};



#endif //REGULAR_EXPRESSION_ENGINE_REGEXSYNTAXANALYZER_H
