#ifndef STRING_H
#define STRING_H

#include <memory>
#include <string>

#include "lexerstate.h"
#include "token.h"

class StringState : public LexerState
{
private:
    bool accepted = false;
    std::string value;

public:
    StringState() : value("") {}
    StringState(std::string so_far) : value(so_far) {}
    ~StringState() {}

    std::unique_ptr<LexerState> event(std::istream& is) override;
    bool accept() override { return accepted; };
    Token get_token() override;
};

#endif
