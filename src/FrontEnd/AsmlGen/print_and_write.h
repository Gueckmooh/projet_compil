/**
 * \file      print_and_write.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     contains all printing functions used in the front end
 *
 * \details
 */
#ifndef _PRINT_AND_WRITE_H_
#define _PRINT_AND_WRITE_H_

#include <stdio.h>

#include "ast.h"
#include "asml_parser_types.h"

void print_term(ptree t);

void print_fd_description(pfundef fd);

void print_all_fd_descriptions();

void print_asml_fun(asml_function_t *t);

void print_asml_asmt(asml_asmt_t *t);

void print_asml_exp(asml_exp_t *t);

void print_asml_fun_args(asml_formal_arg_t *t);

void print_str_list(plist l);

void print_delim_line();
#endif
