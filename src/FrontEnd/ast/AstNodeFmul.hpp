#include "AstNode.hpp"

#ifndef AST_FMUL_NODE_H
#define AST_FMUL_NODE_H


class AstNodeFmul : public AstNode {
protected:
    AstNode *t1;
    AstNode *t2;
public:
    AstNodeFmul(AstNode *t1, AstNode *t2);
    ~AstNodeFmul();

    bool infer_types();
    void print();
};

#endif
