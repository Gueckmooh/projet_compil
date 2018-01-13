#include "env.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *epsilon(env_node *env, char *x){
    char *new_x;
    while(1){
        new_x = epsilon_rec(env, x);
        if (strcmp(new_x, x) == 0){
            return x;
        } else {
            x = new_x;
        }
    }
}


char *epsilon_rec(env_node *env, char *x){
/*
 * Returns epsilon(x)
 */
    if (env == NULL){
        return x;
    } else if (strcmp(x, env->src) == 0){
        return env->dest;
    } else {
        return epsilon(env->next, x);
    }
}

bool is_in_env(env_node *env, char *var_name){
/*
 * Returns true iff var_name is inn env already
 */
    if (env == NULL) {
        return false;
    } else if (strcmp(env->src, var_name) == 0){
        return true;
    } else {
        return is_in_env(env->next, var_name);
    }
}

env_node *gen_env_node(char *src, char *dest, env_node *next){
    env_node *result = malloc(sizeof(env_node));
    result->src = src;
    result->dest = dest;
    result->next = next;
    return result;
}

env_node *gen_env_node_int(char *var_name, int value, env_node *next){
    env_node *result = malloc(sizeof(env_node));
    result->src = var_name;
    result->value = value;
    result->next = next;
    return result;
}

int get_value(char *var_name, env_node *env){
    if(env != NULL){
        if(strcmp(env->src, var_name) == 0){
            return env->value;
        } else {
            return get_value(var_name, env->next);
        }
    } else {
        return 0;
    }
}
