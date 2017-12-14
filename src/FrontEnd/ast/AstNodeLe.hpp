#include "AstNode.hpp"
#include "AstVisitor.hpp"

#ifndef AST_LE_NODE_H
#define AST_LE_NODE_H


class AstNodeLe  :public AstNode {
protected:
    AstNode *t1, *t2;
public:
    AstNodeLe(AstNode *t1, AstNode *t2);
    ~AstNodeLe();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
