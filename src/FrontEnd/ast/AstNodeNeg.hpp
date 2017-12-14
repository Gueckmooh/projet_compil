
#ifndef AST_NEG_NODE_H
#define AST_NEG_NODE_H

#include "AstNodeUnary.hpp"
#include "config.h"

class AstNodeNeg : public AstNodeUnary {
public:
    AstNodeNeg(AstNode *t1);
    ~AstNodeNeg();

    bool infer_types();
    void print(int indent);
};

#endif
