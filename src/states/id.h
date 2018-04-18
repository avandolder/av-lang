#ifndef ID_H
#define ID_H

#include <memory>
#include <string>

#include "lexerstate.h"
#include "token.h"

class IdState : public LexerState
{
private:
    bool accepted = false;
    std::string id;

public:
    IdState(std::string so_far) : id(so_far) {}
    ~IdState() {}

    std::unique_ptr<LexerState> event(std::istream& is) override;
    bool accept() override { return accepted; };
    Token get_token() override;
};

#endif
