#include <istream>
#include <list>

#include "lexer.h"
#include "token.h"
#include "states/initstate.h"

void Lexer::scan()
{
    while (!input.eof())
        tokens.push_back(generate_token());
}

void Lexer::generate_token()
{
    
}

std::list<Token> Lexer::tokenize(std::istream& input)
{
    Lexer lexer(input);
    lexer.scan();
    return std::move(lexer.tokens);
}
