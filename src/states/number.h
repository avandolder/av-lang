#ifndef NUMBER_H
#define NUMBER_H

#include <memory>
#include <string>

#include "lexerstate.h"
#include "token.h"

class NumberState : public LexerState
{
private:
    bool accepted = false;
    std::string number;

public:
    NumberState(std::string so_far) : number(so_far) {}
    ~NumberState() {}

    std::unique_ptr<LexerState> event(std::istream& is) override;
    bool accept() override { return accepted; };
    Token get_token() override;
};

#endif
