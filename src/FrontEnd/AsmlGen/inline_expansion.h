#ifndef _INLINE_EXPANSION_H_
#define _INLINE_EXPANSION_H_

#include "ast.h"

#define INLINE_THRESHOLD 4

int get_function_size(ptree t);

ptree apply_inline_expansion(ptree t);

ptree replace_funcall_by_body(pfundef fd, ptree t);

#endif
