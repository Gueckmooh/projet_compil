#ifndef AST_NODE_UNARY_H
#define AST_NODE_UNARY_H

#include "AstNode.hpp"
#include "config.h"

class AstNodeUnary : public AstNode{
protected:
    AstNode *t1;
public:
    AstNodeUnary();
    AstNodeUnary(AstNode *t1);
    ~AstNodeUnary();

    void traversal(AstVisitor *vis);
};

#endif
