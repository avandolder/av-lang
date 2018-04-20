#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast/ast.h"

class Interpreter
{
public:
    static void interpret(Ast tree);
};

#endif
