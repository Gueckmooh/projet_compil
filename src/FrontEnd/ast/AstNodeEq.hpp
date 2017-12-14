#include "AstNode.hpp"
#include "AstVisitor.hpp"

#ifndef AST_EQ_NODE_H
#define AST_EQ_NODE_H


class AstNodeEq  :public AstNode {
protected:
    AstNode *t1, *t2;
public:
    AstNodeEq(AstNode *t1, AstNode *t2);
    ~AstNodeEq();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
