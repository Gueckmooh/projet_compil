#include "AstNode.hpp"

#ifndef AST_ARRAY_NODE_H
#define AST_ARRAY_NODE_H


class AstNodeArray : public AstNode {
protected:
    AstNode *t1, *t2;
public:
    AstNodeArray(AstNode *t1, AstNode *t2);
    ~AstNodeArray();

    bool infer_types();
    void print();
};

#endif
