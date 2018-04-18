#ifndef LINECOMMENT_H
#define LINECOMMENT_H

#include <memory>
#include <string>

#include "lexerstate.h"
#include "token.h"

class LineCommentState : public LexerState
{
private:
    bool accepted = false;
    std::string comment;

public:
    LineCommentState(std::string so_far) : comment(so_far) {}

    std::unique_ptr<LexerState> event(std::istream& is) override;
    bool accept() override { return accepted; };
    Token get_token() override;
};

#endif
