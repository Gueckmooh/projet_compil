#ifndef _CLOSURE_H_
#define _CLOSURE_H_

#include "ast.h"
#include "list.h"
#include "env.h"

void detect_free_vars(ptree t, env_node *args);

plist get_list_of_vars_used(ptree t);

plist get_list_of_vars_created(ptree t);

void print_fd_description(pfundef fd);

void print_all_fd_descriptions();

void convert_fd_body();

#endif
