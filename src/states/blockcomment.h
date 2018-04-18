#ifndef BLOCKCOMMENT_H
#define BLOCKCOMMENT_H

#include <memory>
#include <string>

#include "lexerstate.h"
#include "token.h"

class BlockCommentState : public LexerState
{
private:
    bool accepted = false;
    std::string comment;

public:
    BlockCommentState(std::string so_far) : comment(so_far) {}

    std::unique_ptr<LexerState> event(std::istream& is) override;
    bool accept() override { return accepted; };
    Token get_token() override;
};

#endif
