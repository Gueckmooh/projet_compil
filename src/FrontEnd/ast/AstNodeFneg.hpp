#include "AstNode.hpp"

#ifndef AST_FNEG_NODE_H
#define AST_FNEG_NODE_H


class AstNodeFneg : public AstNode {
protected:
    AstNode *t1;
public:
    AstNodeFneg(AstNode *t1);
    ~AstNodeFneg();

    bool infer_types();
    void print();
};

#endif
