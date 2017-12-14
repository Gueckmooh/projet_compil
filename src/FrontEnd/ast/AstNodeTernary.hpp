#ifndef AST_NODE_TERNARY_H
#define AST_NODE_TERNARY_H

#include "AstNode.hpp"

class AstNodeTernary : public AstNode{
protected:
    AstNode *t1, *t2, *t3;
public:
    AstNodeTernary();
    AstNodeTernary(AstNode *t1, AstNode *t2, AstNode *t3);
    ~AstNodeTernary();

    void traversal(AstVisitor *vis);
};

#endif
