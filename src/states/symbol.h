#ifndef SYMBOL_H
#define SYMBOL_H

#include <memory>
#include <string>

#include "lexerstate.h"
#include "token.h"

class SymbolState : public LexerState
{
private:
    bool accepted = false;
    std::string symbol;

public:
    SymbolState(std::string so_far) : symbol(so_far) {}
    ~SymbolState() {}

    std::unique_ptr<LexerState> event(std::istream& is) override;
    bool accept() override { return accepted; };
    Token get_token() override;
};

#endif
