#include <cctype>
#include <memory>
#include <istream>

#include "states/id.h"
#include "lexerstate.h"
#include "token.h"

std::unique_ptr<LexerState> IdState::event(std::istream& is)
{
    char c = is.peek();
    if (std::isalnum(c) || c == '_')
        id += is.get();
    else
        accepted = true;

    return std::make_unique<IdState>(id);
}

Token IdState::get_token()
{
    if (Token::keywords.find(id) != Token::keywords.end())
        return Token(Token::keywords[id], id);

    return Token(Token::ID, id);
}
