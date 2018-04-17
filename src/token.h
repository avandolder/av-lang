#ifndef TOKEN_H
#define TOKEN_H

#include <unordered_map>
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

    static std::unordered_map<std::string, Type> keywords;

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

std::unordered_map<std::string, Token::Type> Token::keywords = {
    {"var", Token::VAR},
    {"func", Token::FUNC},
    {"return", Token::RETURN},
    {"break", Token::BREAK},
    {"continue", Token::CONTINUE},
    {"if", Token::IF},
    {"else", Token::ELSE},
    {"while", Token::WHILE},
    {"for", Token::FOR},
    {"in", Token::IN},
    {"and", Token::AND},
    {"or", Token::OR},
    {"xor", Token::XOR},
    {"not", Token::NOT},
};

#endif
