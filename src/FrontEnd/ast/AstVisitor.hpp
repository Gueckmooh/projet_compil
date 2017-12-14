#ifndef AST_VIS_H
#define AST_VIS_H

#include "AstNode.hpp"

class AstNode;
class FunDef;

class AstVisitor{
protected:
    AstVisitor *next;
public:
    AstVisitor();
    AstVisitor(AstVisitor *next);
    ~AstVisitor();

    void visit_node(AstNode *node);
    void visit_fun_def(FunDef *fun_def);
};


#endif
