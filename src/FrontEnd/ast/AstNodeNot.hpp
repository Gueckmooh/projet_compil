
#ifndef AST_NOT_NODE_H
#define AST_NOT_NODE_H

#include "AstNodeUnary.hpp"
#include "config.h"

class AstNodeNot : public AstNodeUnary {
public:
    AstNodeNot(AstNode *t1);
    ~AstNodeNot();

    bool infer_types();
    void print(int indent);
};

#endif
