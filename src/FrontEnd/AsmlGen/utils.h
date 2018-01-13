#ifndef UTILS_H
#define UTILS_H

#include "ast.h"
#include "list.h"

#define VARNAME_SIZE 16

#define ASML_FUNC_PREFIX "_min_caml_"

char *cpy_str(char *src);

char *gen_varname();

char *gen_funcname();

char *prefix_funcname();

char *int_to_str(int i);

#endif
