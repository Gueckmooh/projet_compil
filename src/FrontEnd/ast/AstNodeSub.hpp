
#ifndef AST_SUB_NODE_H
#define AST_SUB_NODE_H

#include "AstNodeBinary.hpp"

class AstNodeSub : public AstNodeBinary {
public:
    AstNodeSub(AstNode *t1, AstNode *t2);
    ~AstNodeSub();

    bool infer_types();
    void print();
};

#endif
