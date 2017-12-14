
#ifndef AST_PUT_NODE_H
#define AST_PUT_NODE_H

#include "AstNodeTernary.hpp"
#include "config.h"

class AstNodePut  :public AstNodeTernary {
public:
    AstNodePut(AstNode *t1, AstNode *t2, AstNode *t3);
    ~AstNodePut();

    bool infer_types();
    void print(int indent);
};

#endif
