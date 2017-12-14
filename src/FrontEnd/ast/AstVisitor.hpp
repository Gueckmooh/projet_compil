#ifndef AST_VIS_H
#define AST_VIS_H

#include "AstNode.hpp"
#include "config.h"

class AstNode;
class FunDef;

class AstVisitor{
protected:
    AstVisitor *next;
public:
    AstVisitor();
    AstVisitor(AstVisitor *next);
    ~AstVisitor();

    virtual void visit_node(AstNode *node);
    virtual void visit_fun_def(FunDef *fun_def);
};


#endif
