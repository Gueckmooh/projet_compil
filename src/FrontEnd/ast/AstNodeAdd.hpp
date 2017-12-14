
#ifndef AST_ADD_NODE_H
#define AST_ADD_NODE_H

#include "AstNode.hpp"

class AstNodeAdd : public AstNode {
protected:
    AstNode *t1;
    AstNode *t2;
public:
    AstNodeAdd(AstNode *t1, AstNode *t2);
    ~AstNodeAdd();

    bool infer_types();
    void print();
};

#endif
