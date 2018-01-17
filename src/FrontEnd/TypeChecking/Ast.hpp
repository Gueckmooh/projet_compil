/**
 * \file      Ast.hpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Ast Builder for TypeChecking
 * \details
 * this file defines class for Ast
 * this class builds an Ast from an min-ml file or a ptree
 * then can apply an AstVisitor onto it
 */
 
#ifndef AST_H
#define AST_H

#include "print_ast.h"
#include "AstVisitor.hpp"
#include "Strategy.hpp"

class AstNode ;
class AstVisitor;
class Strategy;

/* !
 * \class Ast
 */

class Ast {
private :
    std::ostream * os ;
    AstNode * root ;
public:
    ptree ast ;
    Ast();
    Ast(ptree ast);
    Ast(ptree ast, std::ostream * os);
    Ast(const char* filename);
    Ast(const char* filename, std::ostream * os);
    std::ostream& getOs() const;
    static AstNode * build_ast(ptree t) ;
    void visitAst (AstVisitor * vis) ;
    virtual ~Ast();
};

#endif	/* AST_H */
