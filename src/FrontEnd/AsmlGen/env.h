#ifndef ENV_H
#define ENV_H

#include "list.h"

typedef struct {
    char *src, *dest;
} str_to_str;

plist cpy_env(plist l);

void add_or_replace(plist env, str_to_str *element);

char *epsilon(plist env, char *x);

str_to_str *new_str_to_str(char *src, char *dest);

#endif
