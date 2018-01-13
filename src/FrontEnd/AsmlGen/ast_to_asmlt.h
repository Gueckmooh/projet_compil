#ifndef AST_TO_ASMLT_H
#define AST_TO_ASMLT_H

#include "asml_parser_types.h"
#include "ast.h"

// #define _ALLOCATE_BYTES_
// if defined, call mem 4 to allocate an array of size 1 ; if not, call
// mem 1 to allocate an array of size 1.

#ifdef _ALLOCATE_BYTES_
    #define WORD_SIZE 4
#else
    #define WORD_SIZE 1
#endif


asml_function_t *build_asml_from_ptree(ptree t);

asml_asmt_t *to_asml_asmt(ptree t);

asml_exp_t *to_asml_exp(ptree t);

asml_formal_arg_t *args_list_to_asml_args_list(plist ast_args_list);

asml_formal_arg_t *string_list_to_asml_args_list(plist str_list);

void send_func_d_to_asml_parser(ptree t);

asml_asmt_t *lettuple_to_asmlt(ptree t);

asml_asmt_t *tuple_to_asml_asmt(ptree t);

void print_asml_fun(asml_function_t *t);

void print_asml_asmt(asml_asmt_t *t);

void print_asml_exp(asml_exp_t *t);

void print_asml_fun_args(asml_formal_arg_t *t);
#endif
