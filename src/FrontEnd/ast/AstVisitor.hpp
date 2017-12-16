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

    virtual void visit_node_start(AstNode *node);
    virtual void visit_node_end(AstNode *node);


    virtual void visit_fun_def_start(FunDef *fun_def);
    virtual void visit_fun_def_end(FunDef *fun_def);
};


#endif
