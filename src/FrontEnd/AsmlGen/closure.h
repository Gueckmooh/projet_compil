#ifndef _CLOSURE_H_
#define _CLOSURE_H_

#include "ast.h"
#include "list.h"
#include "env.h"

ptree apply_closure_conversion(ptree t);

ptree apply_clos(ptree t);

ptree add_free_vars_refs(pfundef fd, listNode *current_var, int offset);
#endif
