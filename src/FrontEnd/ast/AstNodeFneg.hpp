
#ifndef AST_FNEG_NODE_H
#define AST_FNEG_NODE_H

#include "AstNodeUnary.hpp"
#include "AstVisitor.hpp"

class AstNodeFneg : public AstNodeUnary {
public:
    AstNodeFneg(AstNode *t1);
    ~AstNodeFneg();

    bool infer_types();
    void print();
};

#endif
