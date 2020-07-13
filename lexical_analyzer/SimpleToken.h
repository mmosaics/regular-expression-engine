//
// Created by 胡凌瑞 on 2020/7/14.
//

#ifndef REGULAR_EXPRESSION_ENGINE_SIMPLETOKEN_H
#define REGULAR_EXPRESSION_ENGINE_SIMPLETOKEN_H

#include "Token.h"

class SimpleToken : public Token {

private:
    TokenType tokenType;
    string attribute;
    bool hasAttribute;

public:
    TokenType getTokenType() const;

    void setTokenType(TokenType tokenType);

    const string &getAttribute1() const;

    void setAttribute(const string &attribute);

    bool isHasAttribute() const;

    void setHasAttribute(bool hasAttribute);

};


#endif //REGULAR_EXPRESSION_ENGINE_SIMPLETOKEN_H
