
#ifndef AST_FSUB_NODE_H
#define AST_FSUB_NODE_H

#include "AstNode.hpp"

class AstNodeFsub : public AstNode {
protected:
    AstNode *t1;
    AstNode *t2;
public:
    AstNodeFsub(AstNode *t1, AstNode *t2);
    ~AstNodeFsub();

    bool infer_types();
    void print();
};

#endif
