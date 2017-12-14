#include "AstNode.hpp"

#ifndef AST_NEG_NODE_H
#define AST_NEG_NODE_H


class AstNodeNeg : public AstNode {
protected:
    AstNode *t1;
public:
    AstNodeNeg(AstNode *t1);
    ~AstNodeNeg();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
