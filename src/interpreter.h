#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "value.h"
#include "ast/ast.h"

class Interpreter {
  struct VarFrame {
    std::unordered_map<std::string, std::shared_ptr<Value>> vars;
    bool is_func = false; // Is this stack frame the outermost
                          // frame of a function?
  };

  Ast tree;
  std::vector<VarFrame> var_stack;

public:
  Interpreter(Ast tree) : tree(tree) {}

  static void interpret(Ast tree);

  std::shared_ptr<Value> eval_function(
      std::string id, std::vector<std::shared_ptr<Ast::Expr>> params);
  std::shared_ptr<Value> eval_statement(std::shared_ptr<Ast::Stmt> stmt);
  std::shared_ptr<Value> eval_expression(std::shared_ptr<Ast::Expr> expr);
  std::string define_variable(std::shared_ptr<Ast::VarDef> def);
  void assignment(std::shared_ptr<Ast::Assign> stmt);
};

#endif
