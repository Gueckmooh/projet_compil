#ifndef _MAP_VAR_AND_FUNC_H_
#define _MAP_VAR_AND_FUNC_H_

#include "ast.h"
#include "env.h"

ptree eliminate_unnecessary_defs(ptree t);

ptree remove_unused_vars(ptree t);

plist get_list_of_vars_used(ptree t);

plist get_list_of_vars_created(ptree t);

void map_functions(ptree t, env_node *env);

#endif
