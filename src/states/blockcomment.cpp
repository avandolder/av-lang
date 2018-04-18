#include <cctype>
#include <memory>
#include <istream>

#include "lexerstate.h"
#include "token.h"
#include "states/blockcomment.h"

std::unique_ptr<LexerState> BlockCommentState::event(std::istream& is)
{
    char c = is.get();

    if (c == '*' && is.peek() == '/')
    {
        // End of comment reached.
        is.get();
        accepted = true;
    }
    else
        comment += c;

    return std::make_unique<BlockCommentState>(comment);
}

Token BlockCommentState::get_token()
{
    return Token(Token::COMMENT, comment);
}
