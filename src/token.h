#ifndef TOKEN_H
#define TOKEN_H

#include <unordered_map>
#include <string>
#include <vector>

#include "trie.h"

class Token
{
public:
    enum Type
    {
        ERROR,
        END,
        COMMENT,
        SEMI,
        COLON,
        COMMA,
        VAR,
        ID,
        ASSIGN,
        ADDASSIGN,
        SUBASSIGN,
        MULASSIGN,
        DIVASSIGN,
        POWASSIGN,
        MODASSIGN,
        BITANDASSIGN,
        BITORASSIGN,
        BITXORASSIGN,
        BITNOTASSIGN,
        BITSHLASSIGN,
        BITSHRASSIGN,
        FUNC,
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
        BITSHL,
        BITSHR,
    };

    static std::unordered_map<std::string, Type> keywords;
    static Trie<Type> symbols;
    static std::vector<std::string> type_names;

    Token() {}
    Token(Type t) : type(t) {}
    Token(Type t, std::string v) : type(t), value(v) {}

    Type type;
    std::string value;

    bool operator==(const Type& t) { return type == t; }
    bool operator!=(const Type& t) { return type != t; }
    operator Type() { return type; }
};

#endif
