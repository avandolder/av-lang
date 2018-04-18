#include <cctype>
#include <istream>
#include <list>
#include <string>

#include "lexer.h"
#include "token.h"
#include "states/id.h"
#include "states/number.h"
#include "states/string.h"
#include "states/symbol.h"

void Lexer::scan()
{
    Token token = generate_token();
    while (token != Token::END)
    {
        tokens.push_back(token);
        token = generate_token();
    }
}

Token Lexer::generate_token()
{
    // Skip leading whitespace.
    while (!input.eof() && std::isspace(input.peek()))
        input.get();

    if (input.eof())
        return Token(Token::END);

    // Determine which state to initialize the FSM to.
    curr_state = nullptr;
    char c = input.get();
    if (std::isalpha(c) || c == '_')
        curr_state = std::make_unique<IdState>(std::string(1, c));
    else if (c == '\"')
        curr_state = std::make_unique<StringState>();
    else if (std::isdigit(c))
        curr_state = std::make_unique<NumberState>(std::string(1, c));
    else if (Token::symbols.has_child(c))
       curr_state = std::make_unique<SymbolState>(std::string(1, c));
    else
        return Token(Token::ERROR);

    auto next_state = curr_state->event(input);
    while (!curr_state->accept())
    {
        curr_state = std::move(next_state);
        next_state = curr_state->event(input);
    }

    return curr_state->get_token();
}

std::list<Token> Lexer::tokenize(std::istream& input)
{
    Lexer lexer(input);
    lexer.scan();
    return std::move(lexer.tokens);
}
