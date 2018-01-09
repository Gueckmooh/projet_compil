#include <iostream>
#include <fstream>

#define TYPECHECKING_SUCCESS 0
#define TYPECHECKING_FAILURE 1

#ifndef __TYPE_CALLER_H__
#define __TYPE_CALLER_H__

#include "Ast.hpp"

int typeChecking (Ast & ast);

int init_tc(ptree ptree_ast);

#endif
