#ifndef LEXERSTATE_H
#define LEXERSTATE_H

#include <istream>
#include <memory>

#include "token.h"

class LexerState
{
public:
    LexerState() {}
    virtual ~LexerState() = 0;

    virtual std::shared_ptr<LexerState> event(std::istream& is) = 0;
    virtual bool accept() = 0;
    virtual Token get_token() = 0;
};

#endif