#ifndef AST_TREE_H
#define AST_TREE_H

#include <memory>
#include <string>
#include <unordered_map>

class Ast {
 public:
  // Define all the possible node types.
  class Node {
   public:
    virtual ~Node() {}
  };

  class FuncDef;
  class VarDef;
  class Block;

  // Define all expressions.
  class Expr;
  class BinaryExpr;
  class UnaryExpr;
  class Term;
  class FuncTerm;

  // Define all statements.
  class Stmt;
  class If;
  class While;
  class For;
  class Return;
  class Break;
  class Continue;
  class Assign;
  class FuncCall;

  std::unordered_map<std::string, std::shared_ptr<FuncDef>> func;
  std::unordered_map<std::string, std::shared_ptr<VarDef>> var;
};

#endif
