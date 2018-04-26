#ifndef LEXER_H
#define LEXER_H

#include <istream>
#include <list>
#include <memory>

#include "token.h"

class Lexer {
 public:
  Lexer(std::istream& input) : input(input) {}

  static std::list<Token> tokenize(std::istream& input);

  void scan();
  Token generate_token();

  Token get_id();
  Token get_number();
  Token get_string();
  Token get_symbol();
  Token get_line_comment();
  Token get_block_comment();

 private:
  std::list<Token> tokens;
  std::istream& input;
  int newlines = 0;
};

#endif
