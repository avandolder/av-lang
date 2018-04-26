#ifndef AST_EXPR_H
#define AST_EXPR_H

#include <memory>
#include <string>
#include <vector>

#include "ast/ast.h"

class Ast::Expr : public Node {
 public:
  enum Type {
    BINARY,
    UNARY,
    ID,
    STRING,
    NUMBER,
    FUNC,
  };

  virtual ~Expr() {}
  virtual Type get_type() = 0;
};

class Ast::BinaryExpr : public Expr {
 public:
  std::string op;
  std::shared_ptr<Expr> lhs;
  std::shared_ptr<Expr> rhs;

  Type get_type() { return BINARY; };
};

class Ast::UnaryExpr : public Expr {
 public:
  std::string op;
  std::shared_ptr<Expr> expr;

  Type get_type() { return UNARY; };
};

class Ast::Term : public Expr {
 public:
  Type type;
  std::string value;

  Term(Type t, std::string v) : type(t), value(v) {}

  Type get_type() { return type; };
};

class Ast::FuncTerm : public Expr {
 public:
  std::string id;
  std::vector<std::shared_ptr<Expr>> params;

  Type get_type() { return FUNC; };
};

#endif
