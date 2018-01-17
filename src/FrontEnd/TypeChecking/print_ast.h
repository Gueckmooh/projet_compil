/**
 * \file      print_ast.h
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     ptree printing
 *
 */

#ifndef PRINT_AST_H
#define	PRINT_AST_H

#include <assert.h>
#include <stdio.h>
#include "ast.h"
#include "list.h"

#ifdef	__cplusplus
extern "C" {
#endif

void print_binary(char *op, ptree t1, ptree t2) ;

void print_id(id i) ;

void print_unary(char *op, ptree t) ;

// precondition: list is not empty
void print_list(plist l, char *sep, void f(void *)) ;

void print_term(ptree t) ;

ptree free_ast(ptree t);

extern FILE *yyin;
extern int yydebug;
extern int yyparse(ptree *ast);


#ifdef	__cplusplus
}
#endif

#endif	/* PRINT_AST_H */

