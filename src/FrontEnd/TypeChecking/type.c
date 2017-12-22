#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"
#include "ast.h"

#define MAX_BUF 6

char buffer[MAX_BUF];

ptype gentvar() {
    static int cnt = 0;
    ptype res = (ptype) malloc(sizeof(type));
    res->code = TY_VAR;
    buffer[0] = '?';
    buffer[1] = 't';
    res->params.var = (char *) malloc(sizeof(buffer));
    snprintf(buffer+2, sizeof(cnt), "%d", cnt);
    strncpy(res->params.var, buffer, sizeof(buffer) -1 );
    cnt++;
    return res;
}

ptype copy_type(ptype original_type){
    // TODO -> real copy if needed
    return original_type;
}
