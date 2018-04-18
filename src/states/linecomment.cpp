#include <cctype>
#include <memory>
#include <istream>

#include "lexerstate.h"
#include "token.h"
#include "states/linecomment.h"

std::unique_ptr<LexerState> LineCommentState::event(std::istream& is)
{
    char c = is.get();

    if (c == '\n')
        accepted = true;
    else
        comment += c;

    return std::make_unique<LineCommentState>(comment);
}

Token LineCommentState::get_token()
{
    return Token(Token::COMMENT, comment);
}
