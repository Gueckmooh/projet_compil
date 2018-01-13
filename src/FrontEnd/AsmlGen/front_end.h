#ifndef _FRONT_END_H_
#define _FRONT_END_H_

#include "ast.h"

// debug -> prints ast step by step if defined
#define _AST_DEBUG_

#ifdef _AST_DEBUG_
#define PRINT_AST_STEP_BY_STEP 1
#else
#define PRINT_AST_STEP_BY_STEP 0
#endif

int parsecall(ptree* p, char* fichier);

int parseprint(ptree p, char* fichier);

ptree ast_transform(ptree t);

#endif
