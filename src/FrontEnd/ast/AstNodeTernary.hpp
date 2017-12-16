#ifndef AST_NODE_TERNARY_H
#define AST_NODE_TERNARY_H

#include "AstNode.hpp"
#include "config.h"


/*
    Parent class : AstNodeTernary
*/

class AstNodeTernary : public AstNode{
protected:
    AstNode *t1, *t2, *t3;
public:
    AstNodeTernary();
    AstNodeTernary(AstNode *t1, AstNode *t2, AstNode *t3);
    ~AstNodeTernary();

    void traversal(AstVisitor *vis);
};


/*
    Children classes of AstNodeTernary
*/

//If
class AstNodeIf  :public AstNodeTernary {
public:
    AstNodeIf(AstNode *t1, AstNode *t2, AstNode *t3);
    ~AstNodeIf();

    bool infer_types();
    void print(int indent);
};

//Put
class AstNodePut  :public AstNodeTernary {
public:
    AstNodePut(AstNode *t1, AstNode *t2, AstNode *t3);
    ~AstNodePut();

    bool infer_types();
    void print(int indent);
};
#endif
