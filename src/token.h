#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
public:
    enum Type
    {
        ERROR,
        SEMI,
        COLON,
        VAR,
        ID,
        ASSIGN,
        ADDASSIGN,
        SUBASSIGN,
        MULASSIGN,
        DIVASSIGN,
        MODASSIGN,
        FUNC,
        COMMA,
        LPAR,
        RPAR,
        LBRA,
        RBRA,
        RETURN,
        BREAK,
        CONTINUE,
        IF,
        ELSE,
        WHILE,
        FOR,
        IN,
        STRING,
        NUMBER,
        EQUAL,
        NOTEQUAL,
        LT,
        GT,
        LTE,
        GTE,
        AND,
        OR,
        XOR,
        NOT,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        POWER,
        MODULO,
        BITAND,
        BITOR,
        BITXOR,
        BITNOT,
    };

    Token() {}
    Token(Type t) : type(t) {}
    Token(Type t, std::string v) : type(t), value(v) {}

    Type type;
    std::string value;

    bool operator==(Type t)
    {
        return type == t;
    }
};

#endif
