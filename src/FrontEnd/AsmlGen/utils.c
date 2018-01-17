#include "utils.h"
#include "front_end.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stdbool.h"

extern int varname_counter;
extern int funcname_counter;
extern plist fd_list;

char *cpy_str(char *src){
    char *res = malloc(strlen(src) + 1);
    strcpy(res,src);
    return res;
}

char *gen_varname(){
    char *res = malloc(VARNAME_SIZE);
    sprintf(res,"v%d", varname_counter);
    varname_counter ++;
    return res;
}

char *gen_funcname(){
    char *res = malloc(VARNAME_SIZE);
    sprintf(res,"_f%d", funcname_counter);
    funcname_counter ++;
    return res;
}

char *prefix_funcname(char * funcname){
    char *new_funcname = malloc(strlen(funcname) + strlen(ASML_FUNC_PREFIX) + 1);
    strcpy(new_funcname, ASML_FUNC_PREFIX);
    strcat(new_funcname, funcname);
    return new_funcname;
}

char *int_to_str(int i){
    char *res = malloc(VARNAME_SIZE);
    sprintf(res,"%d", i);
    return res;
}

bool is_a_label(char *str){
    assert(str);
    return (*str == '_');
}


pfundef get_fd(char *label){
    assert(is_a_label(label));
    listNode *l_node = fd_list->head;
    pfundef fd;
    while(l_node != NULL){
        fd = (pfundef)l_node->data;
        if(strcmp(fd->var, label) == 0){
            return fd;
        }
        l_node = l_node->next;
    }
    // case -> fd was not found, it's a label to an external function
    // (should be prefixed by _min_caml_)
    return NULL;
}

pfundef alloc_fd(){
    pfundef res = malloc(sizeof(struct fundef));
    return res;
}

plist eliminate_doubles_in_str_list(plist l){
    listNode *l_node = l->head;
    plist result = empty();
    while(l_node != NULL){
        if (!is_in_str_list(result, (char *)l_node->data)){
            result = (
                result->head == NULL ?
                cons(l_node->data, empty()) :
                append(result, cons(l_node->data, empty()))
            );
        }
        l_node = l_node->next;
    }
    return result;
}
