#ifndef AST_VIS_PRINT_H
#define AST_VIS_PRINT_H

#include "AstVisitor.hpp"
#include "AstNode.hpp"
#include "FunDef.hpp"
#include "config.h"


class AstVisPrint : public AstVisitor{
protected:
    int indent;
public:
    AstVisPrint();
    AstVisPrint(AstVisitor *next);
    ~AstVisPrint();

    void visit_node(AstNode *node);
    void visit_fun_def(FunDef *fun_def);
};

#endif
