#ifndef AST_H
#define AST_H

#include "print_ast.h"
#include "AstVisitor.hpp"
#include "Strategy.hpp"

class AstNode ;
class AstVisitor;
class Strategy;

class Ast {
private :
    AstNode * root ;
public:
    ptree ast ;
    Ast();
    Ast(ptree ast);
    Ast(const char* filename) ;
    static AstNode * build_ast(ptree t) ;
    void visitAst (AstVisitor * vis) ;
    virtual ~Ast();
};

#endif	/* AST_H */