#include "AstNode.hpp"
#include "AstVisitor.hpp"

#ifndef AST_GET_NODE_H
#define AST_GET_NODE_H


class AstNodeGet  :public AstNode {
protected:
    AstNode *t1, *t2;
public:
    AstNodeGet(AstNode *t1, AstNode *t2);
    ~AstNodeGet();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
