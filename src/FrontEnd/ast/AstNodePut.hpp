#include "AstNode.hpp"

#ifndef AST_PUT_NODE_H
#define AST_PUT_NODE_H


class AstNodePut  :public AstNode {
protected:
    AstNode *t1, *t2, *t3;
public:
    AstNodePut(AstNode *t1, AstNode *t2, AstNode *t3);
    ~AstNodePut();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
