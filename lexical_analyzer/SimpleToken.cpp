//
// Created by 胡凌瑞 on 2020/7/14.
//

#include "SimpleToken.h"

TokenType SimpleToken::getTokenType() const {
    return tokenType;
}

void SimpleToken::setTokenType(TokenType tokenType) {
    SimpleToken::tokenType = tokenType;
}

const string &SimpleToken::getAttribute1() const {
    return attribute;
}

void SimpleToken::setAttribute(const string &attribute) {
    SimpleToken::attribute = attribute;
}

bool SimpleToken::isHasAttribute() const {
    return hasAttribute;
}

void SimpleToken::setHasAttribute(bool hasAttribute) {
    SimpleToken::hasAttribute = hasAttribute;
}
