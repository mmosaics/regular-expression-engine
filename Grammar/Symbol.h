//
// Created by 胡凌瑞 on 2021/1/16.
//

#ifndef REGULAR_EXPRESSION_ENGINE_SYMBOL_H
#define REGULAR_EXPRESSION_ENGINE_SYMBOL_H

#include <utility>
#include "string"
#include "GlobalVariable.h"

enum TerminalType{Terminal, Nonterminal};

class Symbol {

private:
    TerminalType type;
    std::string symbolName;
    char value = EPSILON;
    friend class Builder;

public:
    TerminalType getType() const {
        return type;
    }

    const std::string &getSymbolName() const {
        return symbolName;
    }

    char getValue() const {
        return value;
    }

public:
    class Builder {
    private:
        Symbol* result;
    public:
        Builder() = default;
        Builder &type(TerminalType t) {
            result->type = t;
            return *this;
        }
        Builder &symbolName(std::string name) {
            result->symbolName = std::move(name);
            return *this;
        }
        Builder &value(char val) {
            result->value = val;
            return *this;
        }
        Symbol* build() {
            return result;
        }
    };
};


#endif //REGULAR_EXPRESSION_ENGINE_SYMBOL_H
