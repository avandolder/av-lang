#include <memory>
#include <istream>

#include "states/string.h"
#include "lexerstate.h"
#include "token.h"

std::unique_ptr<LexerState> StringState::event(std::istream& is)
{
    char c = is.get();
    if (c == '\"')
        accepted = true;
    else if (c == '\\')
        switch (is.get())
        {
            case '\\': value += '\\'; break;
            case '\"': value += '\"'; break;
            case 'n': value += '\n'; break;
            case 'r': value += '\r'; break;
            case 't': value += '\t'; break;
        }
    else
        value += c;

    return std::make_unique<StringState>(value);
}

Token StringState::get_token()
{
    return Token(Token::STRING, value);
}
