#ifndef ENV_H
#define ENV_H

#include "list.h"

#include <stdbool.h>

typedef struct {
    char *src, *dest;
} str_to_str;

typedef struct env_node_t{
    char *src, *dest;
    int value;
    struct env_node_t *next;
} env_node;

char *epsilon(env_node *env, char *x);

char *epsilon_rec(env_node *env, char *x);

bool is_in_env(env_node *env, char *var_name);

env_node *gen_env_node(char *src, char *dest, env_node *next);

env_node *gen_env_node_int(char *var_name, int value, env_node *next);

int get_value(char *var_name, env_node *env);
#endif
