#ifndef AST_NOT_NODE_H
#define AST_NOT_NODE_H

#include "AstNode.h"

class AstNodeNot  :public AstNode {
protected:
    Ast *t1;
public:
    AstNodeNot();
    AstNodeNot(const Ast& orig);
    bool inferer_types();
    void print();
    ~AstNodeNot();
};

#endif
