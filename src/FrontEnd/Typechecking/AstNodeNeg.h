#ifndef AST_NEG_NODE_H
#define AST_NEG_NODE_H

#include "AstNode.h"

class AstNodeNeg  :public AstNode {
protected:
    Ast *t1;
public:
    AstNodeNeg();
    AstNodeNeg(const Ast& orig);
    bool inferer_types();
    void print();
    ~AstNodeNeg();
};

#endif
