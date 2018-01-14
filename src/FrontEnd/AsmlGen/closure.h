#ifndef _CLOSURE_H_
#define _CLOSURE_H_

#include "ast.h"
#include "list.h"
#include "env.h"

ptree apply_closure_conversion(ptree t);

ptree apply_clos(ptree t);

pfundef get_fd(char *label);

#endif
