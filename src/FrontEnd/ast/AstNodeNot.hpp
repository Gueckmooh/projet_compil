#include "AstNode.hpp"

#ifndef AST_NOT_NODE_H
#define AST_NOT_NODE_H


class AstNodeNot : public AstNode {
protected:
    AstNode *t1;
public:
    AstNodeNot(AstNode *t1);
    ~AstNodeNot();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
