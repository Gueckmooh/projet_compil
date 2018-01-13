#ifndef _CONSTANT_FOLDING_H_
#define _CONSTANT_FOLDING_H_

#include <stdbool.h>

#include "ast.h"
#include "env.h"

ptree apply_constant_folding(ptree t);

ptree constant_folding(ptree t, env_node *env);

bool can_fold(char *var_name, ptree t);

ptree replace_var(ptree t, env_node *env);
#endif
