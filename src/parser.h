#ifndef PARSER_H
#define PARSER_H

#include <list>

#include "syntaxtree.h"
#include "token.h"

class Parser
{
private:
    std::list<Token> tokens;
    SyntaxTree syntax_tree;

public:
    Parser(std::list<Token> ts) : tokens(ts) {}

    void parse();
    static SyntaxTree parse(std::list<Token> ts);
};

#endif
