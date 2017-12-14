#ifndef AST_NODE_BINARY_H
#define AST_NODE_BINARY_H

#include "AstNode.hpp"
#include "config.h"

class AstNodeBinary : public AstNode{
protected:
    AstNode *t1, *t2;
public:
    AstNodeBinary();
    AstNodeBinary(AstNode *t1, AstNode *t2);
    ~AstNodeBinary();

    void print(int indent);
    void traversal(AstVisitor *vis);
};

#endif
