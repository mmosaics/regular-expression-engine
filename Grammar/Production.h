//
// Created by 胡凌瑞 on 2021/1/16.
//

#ifndef REGULAR_EXPRESSION_ENGINE_PRODUCTION_H
#define REGULAR_EXPRESSION_ENGINE_PRODUCTION_H
#include <utility>

#include "Symbol.h"
#include "vector"

class Production {

private:
    Symbol *start;
    std::vector<Symbol *> body;
    friend class Builder;

public:
    Symbol *getStart() const {
        return start;
    }

    const std::vector<Symbol *> &getBody() const {
        return body;
    }

public:
    class Builder {
    private:
        Production* production;
    public:
        Builder() = default;
        Builder &start(Symbol* s){
            production->start = s;
            return *this;
        }
        Builder &body(Symbol* s) {
            production->body.push_back(s);
            return *this;
        }
        Production* build() {
            return production;
        }
    };
};

#endif //REGULAR_EXPRESSION_ENGINE_PRODUCTION_H
