//
// Created by 胡凌瑞 on 2020/7/13.
//

#ifndef REGULAR_EXPRESSION_ENGINE_TOKEN_H
#define REGULAR_EXPRESSION_ENGINE_TOKEN_H

#include <string>

using std::string;

//简单的词法单元
//对于正则表达式来说，每一个字符都是一个词法单元，目前的词法单元 连接符号 并符号 闭包符号 字符

enum TokenType{CHAR, OPERATOR};

class Token {
    virtual TokenType getTokenType() = 0;
    virtual string getAttribute() = 0;
};


#endif //REGULAR_EXPRESSION_ENGINE_TOKEN_H
