#ifndef AST_NODE_LEAF_H
#define AST_NODE_LEAF_H

#include "AstNode.hpp"

class AstNodeLeaf : public AstNode{
public:
    AstNodeLeaf();
    ~AstNodeLeaf();

    void traversal(AstVisitor *vis);
};

#endif
