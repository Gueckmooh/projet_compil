
#ifndef AST_EQ_NODE_H
#define AST_EQ_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"

class AstNodeEq  :public AstNodeBinary {
public:
    AstNodeEq(AstNode *t1, AstNode *t2);
    ~AstNodeEq();

    bool infer_types();
    void print();
};

#endif
