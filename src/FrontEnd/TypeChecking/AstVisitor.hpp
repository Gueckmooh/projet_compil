/**
 * \file      AstVisitor.hpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Visitor Definition to run through the Ast
 * \details
 * this file defined an AstVisitor :
 * an AstVisitor is divided into 3 sub-visitors
 * each one applies a prefix then infix and finally postfix process
 */

#ifndef AST_VISITOR_H
#define AST_VISITOR_H

#include "AstNode.hpp"
#include <fstream>
#include <iostream>
#include <string>

class AstNode;
class AstVisInfer;
class AstVisitor ;
class AstVisAbstract;

/* !
 * \class AstVisitor
 */

class AstVisitor {
private:
    int ind ;
    int cpt ;
protected:
    AstVisAbstract *prefix, *infix, *postfix ;
    std::ostream * os ;
public:
    const std::string INDENT = "  " ;
    AstVisitor(AstVisAbstract *prefix, AstVisAbstract *infix, AstVisAbstract *postfix);
    AstVisAbstract * GetPrefix() const;
    AstVisAbstract* GetInfix() const;
    AstVisAbstract * GetPostfix() const;
    void setOs(std::ostream* os);
    std::ostream & getOs() ;
    void indent ();
    void unindent ();
    int getIndent () const;
    int getCounter() const;
    void incrCounter() ;
    void resetCounter();
    virtual ~AstVisitor();
};

#endif
