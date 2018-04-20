#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "token.h"
#include "ast/ast.h"

class Parser
{
    Ast tree;
    std::list<Token>& tokens;
    std::list<Token>::iterator itr;

public:
    Parser(std::list<Token>& t) : tokens(t) {}

    static Ast parse(std::list<Token> ts);
    void parse();
    Token& match(Token::Type token);
    void error(Token::Type expected, Token& received);
    Token& peek();
    Token& peek(int n);

    std::shared_ptr<Ast::FuncDef> funcdef();
    std::shared_ptr<Ast::VarDef> param();
    std::shared_ptr<Ast::VarDef> vardef();
    std::shared_ptr<Ast::Block> block();
    std::shared_ptr<Ast::Stmt> stmt();
    std::shared_ptr<Ast::If> ifstmt();
    std::shared_ptr<Ast::While> whilestmt();
    std::shared_ptr<Ast::For> forstmt();
    std::shared_ptr<Ast::Return> returnstmt();
    std::shared_ptr<Ast::Assign> assign();
    std::shared_ptr<Ast::FuncCall> funccall();
    std::shared_ptr<Ast::Expr> expr();
    std::shared_ptr<Ast::Expr> logical_expr();
    std::shared_ptr<Ast::Expr> comparison_expr();
    std::shared_ptr<Ast::Expr> bitwise_expr();
    std::shared_ptr<Ast::Expr> addition_expr();
    std::shared_ptr<Ast::Expr> multiply_expr();
    std::shared_ptr<Ast::Expr> term();
    std::shared_ptr<Ast::FuncTerm> functerm();
};

#endif
