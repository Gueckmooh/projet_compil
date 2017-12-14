#include "AstNode.hpp"

#ifndef AST_IF_NODE_H
#define AST_IF_NODE_H


class AstNodeIf  :public AstNode {
protected:
    AstNode *t1, *t2, *t3;    // if t1 then t2 else t3
public:
    AstNodeIf(AstNode *t1, AstNode *t2, AstNode *t3);
    ~AstNodeIf();

    bool infer_types();
    void print();
};

#endif
