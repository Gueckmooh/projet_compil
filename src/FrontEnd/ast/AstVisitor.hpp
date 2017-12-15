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
    virtual void visit_binary_node1(AstNode *node);
    virtual void visit_ternary_node1(AstNode *node);
    virtual void visit_ternary_node2(AstNode *node);
    
    virtual void visit_fun_def(FunDef *fun_def);
};


#endif
