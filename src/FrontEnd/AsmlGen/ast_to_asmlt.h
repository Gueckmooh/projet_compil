

#ifndef AST_TO_ASMLT_H
#define AST_TO_ASMLT_H

#include "asml_parser_types.h"
#include "ast.h"

asml_function_t *build_asml_from_ptree(ptree t);

asml_asmt_t *to_asml_asmt(ptree t);

asml_exp_t *to_asml_exp(ptree t);

asml_formal_arg_t *args_list_to_asml_args_list(plist ast_args_list);

#endif
