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
            element->dest = new_element->dest;
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


char *epsilon(plist env, char *x){
/*
 * Returns epsilon(x)
 */
    char * res = x;
    str_to_str *env_element;
    listNode *l_node = env->head;
    while(l_node != NULL){
        env_element = (void *)l_node->data;
        if (strcmp(x, env_element->src) == 0){
            res = env_element->dest;
            break;
        }
        l_node = l_node->next;
    }
    return res;
}

str_to_str *new_str_to_str(char *src, char *dest){
    str_to_str *res = malloc(sizeof(str_to_str));
    res->src = src;
    res->dest = dest;
    return res;
}
