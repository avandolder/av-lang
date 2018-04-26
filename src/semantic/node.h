#ifndef SEMANTIC_NODE_H
#define SEMANTIC_NODE_H

#include <memory>
#include <string>

#include "value.h"

class Fst::Node {
 public:
  enum Type {
    JUMP,
    CJMP,
    CALL,
    ADD,
    SUB,
    NEG,
    MUL,
    DIV,
    MOD,
    ASSIGN,
    EQU,
    NEQU,
    GT,
    LT,
    GTE,
    LTE,
    AND,
    OR,
    XOR,
    NOT,
    SHL,
    SHR,
    PUSH,
    RET,
  };

  Node() {}
  Node(Type t) : type(t) {}
  virtual ~Node() {}
  virtual Type get_type() { return type; };

 private:
  Type type;
};

class Fst::Jump : public Node {
 public:
  std::shared_ptr<Node> dest;

  Type get_type() { return JUMP; }
};

class Fst::Call : public Node {
 public:
  std::shared_ptr<Node> dest;

  Type get_type() { return CALL; }
};

class Fst::Assign : public Node {
 public:
  std::string id;

  Type get_type() { return ASSIGN; }
};

class Fst::CondJump : public Node {
 public:
  std::shared_ptr<Node> dest;

  Type get_type() { return CJMP; }
};

class Fst::Push : public Node {
 public:
   std::shared_ptr<Value> value;

   Type get_type() { return PUSH; }
};

#endif
