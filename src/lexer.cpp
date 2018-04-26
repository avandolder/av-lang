#include <cctype>
#include <iostream>
#include <istream>
#include <list>
#include <string>

#include "lexer.h"
#include "token.h"

std::list<Token> Lexer::tokenize(std::istream& input) {
  Lexer lexer(input);
  lexer.scan();
  return std::move(lexer.tokens);
}

void Lexer::scan() {
  Token token = generate_token();

  while (token != Token::END) {
    token.line = newlines;

    if (token != Token::COMMENT)
      tokens.push_back(token);

    token = generate_token();
  }
}

Token Lexer::generate_token() {
  // Skip leading whitespace.
  while (!input.eof() && std::isspace(input.peek()))
    if (input.get() == '\n')
      newlines++;

  if (input.eof())
    return Token(Token::END);

  char c = input.peek();
  if (std::isalpha(c) || c == '_')
    return get_id();
  else if (c == '\"')
    return get_string();
  else if (std::isdigit(c))
    return get_number();
  else if (Token::symbols.has_child(c))
    return get_symbol();

  return Token(Token::ERROR);
}

Token Lexer::get_id() {
  std::string id;

  while (std::isalnum(input.peek()) || input.peek() == '_')
    id += input.get();

  if (Token::keywords.find(id) != Token::keywords.end())
    return Token(Token::keywords[id], id);

  return Token(Token::ID, id);
}

Token Lexer::get_number() {
  std::string number;

  while (std::isdigit(input.peek()))
    number += input.get();

  return Token(Token::NUMBER, number);
}

Token Lexer::get_string() {
  std::string str;

  input.get();  // Read the opening quote.

  while (true) {
    char c = input.get();

    if (c == '\\')
      switch (input.get()) {
        case '\\': str += '\\'; break;
        case '\"': str += '\"'; break;
        case 'n': str += '\n'; break;
        case 'r': str += '\r'; break;
        case 't': str += '\t'; break;
      }
    else if (c == '\"')
      break;
    else
      str += c;
  }

  return Token(Token::STRING, str);
}

Token Lexer::get_symbol() {
  std::string symbol = std::string(1, input.get());

  while (true) {
    auto node = Token::symbols.find(symbol);
    char c = input.peek();

    if (node->has_child(c)) {
      symbol += input.get();
    } else if (symbol == "/" && c == '/') {
      input.unget();
      return get_line_comment();
    } else if (symbol == "/" && c == '*') {
      input.unget();
      return get_block_comment();
    } else {
      break;
    }
  }

  return Token(Token::symbols.find(symbol)->value, symbol);
}

Token Lexer::get_block_comment() {
  std::string comment;
  char c = input.get();

  while (true) {
    if (c == '*' && input.peek() == '/') {
      input.get();
      comment += "*/";
      break;
    } else {
      comment += c;

      if (c == '\n')
        newlines++;
    }

    c = input.get();
  }

  return Token(Token::COMMENT, comment);
}

Token Lexer::get_line_comment() {
  std::string comment;

  while (input.peek() != '\n')
    comment += input.get();

  return Token(Token::COMMENT, comment);
}
