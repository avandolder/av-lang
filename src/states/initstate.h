#ifndef INITSTATE_H
#define INITSTATE_H

#include <memory>
#include <cctype>

#include "lexerstate.h"
#include "states/idstate.h"

class InitState : public LexerState
{
private:


public:
    InitState() {}

    std::shared_ptr<LexerState> event(std::istream& is) override;
    bool accept() override { return false; }
    Token get_token() override;
};

std::shared_ptr<LexerState> event(std::istream& is)
{
    int c = is.peek();

    if (std::isalpha(c))
    {
        return std::make_shared<IdState>();
    }
}

Token InitState::get_token()
{
    // You should never be getting a token from the init state.
    return Token(Token::ERROR);
}

#endif
