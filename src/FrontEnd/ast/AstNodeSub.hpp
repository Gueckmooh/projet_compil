
#ifndef AST_SUB_NODE_H
#define AST_SUB_NODE_H

#include "AstNode.hpp"

class AstNodeSub : public AstNode {
protected:
    AstNode *t1;
    AstNode *t2;
public:
    AstNodeSub(AstNode *t1, AstNode *t2);
    ~AstNodeSub();

    bool infer_types();
    void print();
};

#endif
