#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int varname_counter;
extern int funcname_counter;

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
