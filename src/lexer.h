#ifndef LEXER_H
#define LEXER_H

#include <istream>
#include <list>
#include <memory>

#include "lexerstate.h"
#include "token.h"

class Lexer {
 public:
  Lexer(std::istream& input) : input(input) {}

  Token generate_token();
  void scan();

  static std::list<Token> tokenize(std::istream& input);

 private:
  std::list<Token> tokens;
  std::istream& input;

  std::unique_ptr<LexerState> curr_state;
};

#endif
