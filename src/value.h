#ifndef VALUE_H
#define VALUE_H

#include <string>

class Value
{
 public:
  enum Type
  {
    NUMBER,
    STRING,
    ID,
  };

  virtual ~Value() {}
  virtual Type get_type() = 0;
};

class NumberValue : public Value
{
 public:
  int value;

  Type get_type() { return NUMBER; }
};

class StringValue : public Value
{
 public:
  std::string value;

  Type get_type() { return STRING; }
};

class IdValue : public Value
{
 public:
  std::string id;

  Type get_type() { return ID; }
};

#endif
