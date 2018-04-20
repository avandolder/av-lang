#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>

#include "parser.h"
#include "token.h"
#include "ast/ast.h"
#include "ast/block.h"
#include "ast/expr.h"
#include "ast/funcdef.h"
#include "ast/stmt.h"

Ast Parser::parse(std::list<Token> ts)
{
    Parser p(ts);
    p.parse();
    return std::move(p.tree);
}

void Parser::parse()
{
    itr = tokens.begin();

    while (itr != tokens.end())
        if (peek() == Token::VAR)
        {
            auto node = vardef();
            tree.var.emplace(node->id, node);
        }
        else if (peek() == Token::FUNC)
        {
            auto node = funcdef();
            tree.func.emplace(node->id, node);
        }
        else if (peek() != Token::COMMENT)
            error(Token::FUNC, peek());
}

Token& Parser::match(Token::Type token)
{
    while (*itr == Token::COMMENT)
        itr++;

    if (*itr != token)
        error(token, *itr);

    return *(itr++);
}

void Parser::error(Token::Type expected, Token& received)
{
    std::cout << "parser: error: " << Token::type_names[expected] <<
        " expected, "  << Token::type_names[received] << " " <<
        received.value << " received." << std::endl;

    std::exit(1);
}

Token& Parser::peek()
{
    while (*itr == Token::COMMENT)
        itr++;

    return *itr;
}

Token& Parser::peek(int n)
{
    auto itrn = itr;

    for (int i = 0; i < n; i++)
    {
    	while (*itrn == Token::COMMENT)
        	itrn++;

        itrn++;
    }

    return *itrn;
}

std::shared_ptr<Ast::FuncDef> Parser::funcdef()
{
    auto node = std::make_shared<Ast::FuncDef>();

    match(Token::FUNC);
    node->id = match(Token::ID).value;
    match(Token::LPAR);

    if (peek() != Token::RPAR)
    {
        node->params.push_back(param());

        while (peek() != Token::RPAR)
        {
            match(Token::COMMA);
            node->params.push_back(param());
        }
    }

    match(Token::RPAR);

    if (peek() == Token::COLON)
    {
        match(Token::COLON);

        node->returns_value = true;
        node->return_type = match(Token::ID).value;
    }

    node->block = block();
    return node;
}

std::shared_ptr<Ast::VarDef> Parser::param()
{
    auto param = std::make_shared<Ast::VarDef>();

    param->id = match(Token::ID).value;
    match(Token::COLON);
    param->type = match(Token::ID).value;

    return param;
}

std::shared_ptr<Ast::VarDef> Parser::vardef()
{
    auto node = std::make_shared<Ast::VarDef>();

    match(Token::VAR);
    node->id = match(Token::ID).value;
    match(Token::COLON);
    node->type = match(Token::ID).value;

    // Check if the variable is initialized.
    if (peek() == Token::ASSIGN)
    {
        node->initialized = true;

        match(Token::ASSIGN);
        node->initial_value = expr();
    }

    match(Token::SEMI);
    return node;
}

std::shared_ptr<Ast::Block> Parser::block()
{
    auto node = std::make_shared<Ast::Block>();

    match(Token::LBRA);

    while (peek() != Token::RBRA)
        node->stmts.push_back(stmt());

    match(Token::RBRA);
    return node;
}

std::shared_ptr<Ast::Stmt> Parser::stmt()
{
    switch(peek())
    {
    case Token::IF:
        return std::dynamic_pointer_cast<Ast::Stmt>(ifstmt());
    case Token::WHILE:
        return std::dynamic_pointer_cast<Ast::Stmt>(whilestmt());
    case Token::FOR:
        return std::dynamic_pointer_cast<Ast::Stmt>(forstmt());
    case Token::RETURN:
        return std::dynamic_pointer_cast<Ast::Stmt>(returnstmt());
    case Token::VAR:
        return std::dynamic_pointer_cast<Ast::Stmt>(vardef());

    case Token::BREAK:
        match(Token::BREAK);
        match(Token::SEMI);
        return std::dynamic_pointer_cast<Ast::Stmt>(
                std::make_shared<Ast::Break>());

    case Token::CONTINUE:
        match(Token::CONTINUE);
        match(Token::SEMI);
        return std::dynamic_pointer_cast<Ast::Stmt>(
                std::make_shared<Ast::Continue>());

    case Token::ID:
        if (peek(1) == Token::ASSIGN)
            return std::dynamic_pointer_cast<Ast::Stmt>(assign());
        else if (peek(1) == Token::LPAR)
            return std::dynamic_pointer_cast<Ast::Stmt>(funccall());

    default:
        error(Token::ERROR, peek());
    }
}

std::shared_ptr<Ast::If> Parser::ifstmt()
{
    auto node = std::make_shared<Ast::If>();

    match(Token::IF);
    node->expr = expr();
    node->block = block();

    return node;
}

std::shared_ptr<Ast::While> Parser::whilestmt()
{
    auto node = std::make_shared<Ast::While>();

    match(Token::WHILE);
    node->expr = expr();
    node->block = block();

    return node;
}

std::shared_ptr<Ast::For> Parser::forstmt()
{
    auto node = std::make_shared<Ast::For>();

    match(Token::FOR);
    node->itrid = match(Token::ID).value;

    if (peek() == Token::COLON)
    {
        match(Token::COLON);
        node->itrtype = match(Token::ID).value;
    }

    match(Token::ASSIGN);
    node->start_expr = expr();
    match(Token::COMMA);
    node->end_expr = expr();

    if (peek() == Token::COMMA)
    {
        match(Token::COMMA);
        node->step_expr = expr();
    }

    node->block = block();
    return node;
}

std::shared_ptr<Ast::Return> Parser::returnstmt()
{
    auto node = std::make_shared<Ast::Return>();

    match(Token::RETURN);

    if (peek() != Token::SEMI)
    {
        node->has_value = true;
        node->value = expr();
    }

    match(Token::SEMI);

    return node;
}

std::shared_ptr<Ast::Assign> Parser::assign()
{
    auto node = std::make_shared<Ast::Assign>();

    node->id = match(Token::ID).value;
    match(Token::ASSIGN);
    node->value = expr();
    match(Token::SEMI);

    return node;
}

std::shared_ptr<Ast::FuncCall> Parser::funccall()
{
    auto node = std::make_shared<Ast::FuncCall>();

    node->id = match(Token::ID).value;
    match(Token::LPAR);

    if (peek() != Token::RPAR)
    {
        node->params.push_back(expr());

        while (peek() != Token::RPAR)
        {
            match(Token::COMMA);
            node->params.push_back(expr());
        }
    }

    match(Token::RPAR);
    match(Token::SEMI);
    return node;
}

std::shared_ptr<Ast::Expr> Parser::expr()
{
    // The logical operators have the lowest precedence, and therefore
    // are checked first by the parser.
    return logical_expr();
}

std::shared_ptr<Ast::Expr> Parser::logical_expr()
{
    // Check first if the expression is unary or a bracket.
    if (peek() == Token::NOT)
    {
        auto node = std::make_shared<Ast::UnaryExpr>();
        node->op = match(Token::NOT).value;
        node->expr = logical_expr();
        return std::dynamic_pointer_cast<Ast::Expr>(node);
    }

    // Otherwise, process it as either a binary logical expression
    // or a comparison expression.
    auto node = std::make_shared<Ast::BinaryExpr>();
    node->lhs = comparison_expr();

    switch (peek())
    {
    case Token::AND: node->op = match(Token::AND).value; break;
    case Token::OR: node->op = match(Token::OR).value; break;
    case Token::XOR: node->op = match(Token::XOR).value; break;
    default:
        // This expression has no logical operators in it, so
        // fallthrough to just returning a comparsion expression.
        return node->lhs;
    }

    node->rhs = logical_expr();
    return std::dynamic_pointer_cast<Ast::Expr>(node);
}

std::shared_ptr<Ast::Expr> Parser::comparison_expr()
{
    // Otherwise, process it as either a binary comparison expression
    // or a bitwise expression.
    auto node = std::make_shared<Ast::BinaryExpr>();
    node->lhs = bitwise_expr();

    switch (peek())
    {
    case Token::EQUAL: node->op = match(Token::EQUAL).value; break;
    case Token::NOTEQUAL: node->op = match(Token::NOTEQUAL).value; break;
    case Token::LT: node->op = match(Token::LT).value; break;
    case Token::GT: node->op = match(Token::GT).value; break;
    case Token::LTE: node->op = match(Token::LTE).value; break;
    case Token::GTE: node->op = match(Token::GTE).value; break;
    default:
        // This expression has no comparison operators in it, so
        // fallthrough to just returning a bitwise expression.
        return node->lhs;
    }

    node->rhs = comparison_expr();
    return std::dynamic_pointer_cast<Ast::Expr>(node);
}

std::shared_ptr<Ast::Expr> Parser::bitwise_expr()
{
    // Check first if the expression is unary or a bracket.
    if (peek() == Token::BITNOT)
    {
        auto node = std::make_shared<Ast::UnaryExpr>();
        node->op = match(Token::BITNOT).value;
        node->expr = bitwise_expr();
        return std::dynamic_pointer_cast<Ast::Expr>(node);
    }

    // Otherwise, process it as either a binary logical expression
    // or a comparison expression.
    auto node = std::make_shared<Ast::BinaryExpr>();
    node->lhs = addition_expr();

    switch (peek())
    {
    case Token::BITAND: node->op = match(Token::BITAND).value; break;
    case Token::BITOR: node->op = match(Token::BITOR).value; break;
    case Token::BITXOR: node->op = match(Token::BITXOR).value; break;
    case Token::BITSHL: node->op = match(Token::BITSHL).value; break;
    case Token::BITSHR: node->op = match(Token::BITSHR).value; break;
    default:
        // This expression has no logical operators in it, so
        // fallthrough to just returning a comparsion expression.
        return node->lhs;
    }

    node->rhs = bitwise_expr();
    return std::dynamic_pointer_cast<Ast::Expr>(node);
}

std::shared_ptr<Ast::Expr> Parser::addition_expr()
{
    // Check first if the expression is unary or a bracket.
    if (peek() == Token::MINUS)
    {
        auto node = std::make_shared<Ast::UnaryExpr>();
        node->op = match(Token::MINUS).value;
        node->expr = addition_expr();
        return std::dynamic_pointer_cast<Ast::Expr>(node);
    }

    // Otherwise, process it as either a binary logical expression
    // or a comparison expression.
    auto node = std::make_shared<Ast::BinaryExpr>();
    node->lhs = multiply_expr();

    switch (peek())
    {
    case Token::PLUS: node->op = match(Token::PLUS).value; break;
    case Token::MINUS: node->op = match(Token::MINUS).value; break;
    default:
        // This expression has no logical operators in it, so
        // fallthrough to just returning a comparsion expression.
        return node->lhs;
    }

    node->rhs = addition_expr();
    return std::dynamic_pointer_cast<Ast::Expr>(node);
}

std::shared_ptr<Ast::Expr> Parser::multiply_expr()
{
    // Otherwise, process it as either a binary logical expression
    // or a comparison expression.
    auto node = std::make_shared<Ast::BinaryExpr>();
    node->lhs = term();

    switch (peek())
    {
    case Token::MULTIPLY: node->op = match(Token::MULTIPLY).value; break;
    case Token::DIVIDE: node->op = match(Token::DIVIDE).value; break;
    case Token::POWER: node->op = match(Token::POWER).value; break;
    default:
        // This expression has no logical operators in it, so
        // fallthrough to just returning a comparsion expression.
        return node->lhs;
    }

    node->rhs = term();
    return std::dynamic_pointer_cast<Ast::Expr>(node);
}

std::shared_ptr<Ast::Expr> Parser::term()
{
    // Check first if the term is a bracketed expression.
    if (peek() == Token::LPAR)
    {
        match(Token::LPAR);
        auto node = expr();
        match(Token::RPAR);
        return node;
    }

    switch (peek())
    {
    case Token::ID:
        return std::dynamic_pointer_cast<Ast::Expr>(
            std::make_shared<Ast::Term>(Ast::Expr::ID,
                                        match(Token::ID).value));

    case Token::NUMBER:
        return std::dynamic_pointer_cast<Ast::Expr>(
            std::make_shared<Ast::Term>(Ast::Expr::NUMBER,
                                        match(Token::NUMBER).value));

    case Token::STRING:
        return std::dynamic_pointer_cast<Ast::Expr>(
            std::make_shared<Ast::Term>(Ast::Expr::STRING,
                                        match(Token::STRING).value));

    default:
        error(Token::ID, peek());
    }
}
