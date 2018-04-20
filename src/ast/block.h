#ifndef AST_BLOCK_H
#define AST_BLOCK_H

#include <memory>
#include <vector>

#include "ast/ast.h"

class Ast::Block
{
public:
    std::vector<std::shared_ptr<Stmt>> stmts;
};

#endif
