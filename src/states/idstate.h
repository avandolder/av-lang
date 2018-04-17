#ifndef IDSTATE_H
#define IDSTATE_H

#include <memory>

#include "lexerstate.h"

class IdState : public LexerState
{
private:
    bool accepted = false;

public:
    IdState() {}

    std::shared_ptr<LexerState> event(std::istream& is) override;
    bool accept() override { return accepted; };
    Token get_token() override;
};

#endif
