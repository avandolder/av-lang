#include <cctype>
#include <memory>
#include <istream>

#include "lexerstate.h"
#include "token.h"
#include "states/blockcomment.h"
#include "states/linecomment.h"
#include "states/symbol.h"

std::unique_ptr<LexerState> SymbolState::event(std::istream& is)
{
    auto node = Token::symbols.find(symbol);

    char c = is.peek();
    if (node->has_child(c))
       symbol += is.get();
    else if (symbol == "/" && c == '/')
    {
        is.get();
        return std::make_unique<LineCommentState>("");
    }
    else if (symbol == "/" && c == '*')
    {
        is.get();
        return std::make_unique<BlockCommentState>("");
    }
    else
        accepted = true;

    return std::make_unique<SymbolState>(symbol);
}

Token SymbolState::get_token()
{
    return Token(Token::symbols.find(symbol)->value, symbol);
}
