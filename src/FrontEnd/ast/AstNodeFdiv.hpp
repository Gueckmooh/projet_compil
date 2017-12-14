#include "AstNode.hpp"

#ifndef AST_FDIV_NODE_H
#define AST_FDIV_NODE_H


class AstNodeFdiv : public AstNode {
protected:
    AstNode *t1, *t2;
public:
    AstNodeFdiv(AstNode *t1, AstNode *t2);
    ~AstNodeFdiv();

    bool infer_types();
    void print();
};

#endif
