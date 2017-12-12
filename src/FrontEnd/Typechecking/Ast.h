/* 
 * File:   Ast.h
 * Author: bleuzeb
 *
 * Created on 12 décembre 2017, 12:56
 */

#ifndef AST_H
#define	AST_H

#include <string>
#include "../../pc-archive/c/print_ast.h"


class Ast {
private:
    ptree ast ;
public:
    Ast();
    Ast(const char* nomfich) ;
    Ast(const Ast& orig) ;
    bool inferer_types() ;
    void print() { print_term(ast) ; }
    virtual ~Ast();
};

#endif	/* AST_H */

