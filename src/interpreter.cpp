#include <cstdlib>
#include <iostream>

#include "interpreter.h"
#include "ast/ast.h"
#include "ast/block.h"
#include "ast/expr.h"
#include "ast/funcdef.h"
#include "ast/stmt.h"

void Interpreter::interpret(Ast tree) {
  Interpreter intpr(tree);

  intpr.eval_function("main", {});
}

std::shared_ptr<Value> Interpreter::eval_function(
    std::string id, std::vector<std::shared_ptr<Ast::Expr>> params) {
  if (tree.func.find(id) != tree.func.end()) {
    var_stack.emplace_back();
    var_stack.back().is_func = true;

    // Add the parameters to the local variables.
    for (int i = 0; i < params.size(); i++)
      var_stack.back().vars[tree.func[id]->params[i]->id] =
          eval_expression(params[i]);

    for (auto &stmt : tree.func[id]->block->stmts) {
      if (stmt->get_type() == Ast::Stmt::RETURN) {
        return eval_statement(stmt);
      } else {
        eval_statement(stmt);
      }
    }
  } else {
    std::cout << "interpreter: error: no func " << id << " found\n";
    std::exit(1);
  }
}

std::shared_ptr<Value> Interpreter::eval_statement(
    std::shared_ptr<Ast::Stmt> stmt) {
  switch (stmt->get_type()) {
    case Ast::Stmt::FUNCCALL: {
      auto node = std::static_pointer_cast<Ast::FuncCall>(stmt);
      eval_function(node->id, node->params);
      break;
    }
    case Ast::Stmt::VARDEF:
      define_variable(std::static_pointer_cast<Ast::VarDef>(stmt));
      break;
    case Ast::Stmt::ASSIGN:
      assignment(std::static_pointer_cast<Ast::Assign>(stmt));
      break;
  }
}

std::shared_ptr<Value> Interpreter::eval_expression(
    std::shared_ptr<Ast::Expr> expr) {
}
