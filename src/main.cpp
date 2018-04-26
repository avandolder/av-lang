#include <fstream>
#include <iostream>

#include "interpreter.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char *argv[]) {
  std::ifstream infile(argv[1]);

  Interpreter::interpret(Parser::parse(Lexer::tokenize(infile)));

  return 0;
}
