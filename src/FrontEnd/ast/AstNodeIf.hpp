
#ifndef AST_IF_NODE_H
#define AST_IF_NODE_H

#include "AstNodeTernary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

class AstNodeIf  :public AstNodeTernary {
public:
    AstNodeIf(AstNode *t1, AstNode *t2, AstNode *t3);
    ~AstNodeIf();

    bool infer_types();
    void print(int indent);
};

#endif
