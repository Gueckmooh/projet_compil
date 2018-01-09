#include "env.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

plist cpy_env(plist l){
/*
 * Copy the list l, returns newly created list
 */
    plist res = empty();
    listNode *l_node = l->head, *res_node;
    while(l_node != NULL){
        // create a new node, copy the content
        res_node = malloc(sizeof(listNode));
        res_node->data = l_node->data;
        res_node->next = res->head;
        res->logicalLength ++;
        res->head = res_node;
        l_node = l_node->next;
    }
    return res;
}

void add_or_replace(plist env, str_to_str *new_element){
    listNode *l_node = env->head;
    str_to_str *element;
    while(l_node != NULL){
        element = (str_to_str *)l_node->data;
        if (strcmp(new_element->src, element->src) == 0){
            l_node->data = new_element;
            return;
        }
        l_node = l_node->next;
    }
    listNode *new_node = malloc(sizeof(listNode));
    new_node->data = new_element;
    new_node->next = env->head;
    env->head = new_node;
    env->logicalLength ++;
}

char *epsilon(env_node *env, char *x){
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
