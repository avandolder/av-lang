#include "parser.h"

void Parser::parse()
{
    //
}

SyntaxTree Parser::parse(std::list<Token> ts)
{
    Parser parser(ts);
    parser.parse();
    return parser.syntax_tree;
}
