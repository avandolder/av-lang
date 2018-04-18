#include <cctype>
#include <memory>
#include <istream>

#include "lexerstate.h"
#include "token.h"
#include "states/number.h"

std::unique_ptr<LexerState> NumberState::event(std::istream& is)
{
    char c = is.peek();
    if (std::isdigit(c))
        number += is.get();
    else
        accepted = true;

    return std::make_unique<NumberState>(number);
}

Token NumberState::get_token()
{
    return Token(Token::NUMBER, number);
}
