
#ifndef AST_NEG_NODE_H
#define AST_NEG_NODE_H

#include "AstNodeUnary.hpp"

class AstNodeNeg : public AstNodeUnary {
public:
    AstNodeNeg(AstNode *t1);
    ~AstNodeNeg();

    bool infer_types();
    void print();
};

#endif
