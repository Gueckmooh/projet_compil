#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int knorm_var_counter;
extern int alpha_var_counter;

char *cpy_str(char *src){
    char *res = malloc(strlen(src) + 1);
    strcpy(res,src);
    return res;
}

char *knorm_gen_varname(){
    char *res = malloc(VARNAME_SIZE);
    sprintf(res,"k%d", knorm_var_counter);
    knorm_var_counter ++;
    return res;
}

char *alpha_gen_varname(){
    char *res = malloc(VARNAME_SIZE);
    sprintf(res,"v%d", alpha_var_counter);
    alpha_var_counter ++;
    return res;
}
