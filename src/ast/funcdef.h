#ifndef AST_FUNCDEF_H
#define AST_FUNCDEF_H

#include <memory>
#include <string>
#include <vector>

#include "ast/ast.h"

class Ast::FuncDef
{
public:
    std::string id;
    std::vector<std::shared_ptr<VarDef>> params;
    bool returns_value = false;
    std::string return_type;
    std::shared_ptr<Block> block;
};

#endif
