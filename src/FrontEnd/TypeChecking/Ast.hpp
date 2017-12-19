#ifndef AST_H
#define AST_H

#include "print_ast.h"
#include "AstVisitor.hpp"
#include "Strategy.hpp"

class AstNode ;
class AstVisitor;
class Strategy;

class Ast {
protected:
    Strategy strategy ;
    AstNode * root ;
public:
    Ast();
    Ast(const char* filename) ;
    static AstNode * build_ast(ptree t) ;
    Strategy & getStrategy() ;
    AstNode * getRoot() const;
    virtual ~Ast();
};

#endif	/* AST_H */