#ifndef AST_STMT_H
#define AST_STMT_H

#include <string>
#include <vector>

#include "ast/ast.h"

class Ast::Stmt : public Node {
 public:
  enum Type {
    FUNCCALL,
    VARDEF,
    ASSIGN,
    RETURN,
    BREAK,
    CONTINUE,
    IF,
    WHILE,
    FOR
  };

  virtual ~Stmt() {}
  virtual Type get_type() = 0;
};

class Ast::FuncCall : public Stmt {
 public:
  std::string id;
  std::vector<std::shared_ptr<Ast::Expr>> params;

  Type get_type() override { return FUNCCALL; }
};

class Ast::VarDef : public Stmt {
 public:
  std::string id;
  std::string type;
  bool initialized = false;
  std::shared_ptr<Expr> initial_value = nullptr;

  Type get_type() override { return VARDEF; }
};

class Ast::If : public Stmt {
 public:
  std::vector<std::shared_ptr<Expr>> expr;
  std::vector<std::shared_ptr<Block>> block;

  Type get_type() override { return IF; }
};

class Ast::While : public Stmt {
 public:
  std::shared_ptr<Expr> expr = nullptr;
  std::shared_ptr<Block> block = nullptr;

  Type get_type() override { return WHILE; }
};

class Ast::For : public Stmt {
 public:
  std::string itrid;
  bool declare_itr = false; // Is the iterator a newly declared variable?
  std::string itrtype;
  std::shared_ptr<Expr> start_expr = nullptr;
  std::shared_ptr<Expr> end_expr = nullptr;
  std::shared_ptr<Expr> step_expr = nullptr;
  std::shared_ptr<Block> block = nullptr;

  Type get_type() override { return FOR; }
};

class Ast::Return : public Stmt {
 public:
  bool has_value = false;
  std::shared_ptr<Expr> value;

  Type get_type() override { return RETURN; }
};

class Ast::Assign : public Stmt {
 public:
  std::string id;
  std::shared_ptr<Expr> value = nullptr;

  Type get_type() override { return ASSIGN; }
};

class Ast::Break : public Stmt {
 public:
  Type get_type() override { return BREAK; }
};

class Ast::Continue : public Stmt {
 public:
  Type get_type() override { return CONTINUE; }
};

#endif
