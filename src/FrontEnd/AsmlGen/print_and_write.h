#ifndef _PRINT_AND_WRITE_H_
#define _PRINT_AND_WRITE_H_

#include <stdio.h>

void write_binary(FILE* output,char *op, ptree t1, ptree t2);

void write_id(FILE* output,id i);

void write_unary(FILE* output,char *op, ptree t);

// precondition: list is not empty
void write_list(FILE* output,plist l, char *sep, void f(void *));

void write_term(FILE* output,ptree t);

void print_term(ptree t);
#endif
