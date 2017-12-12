#ifndef AST_IF_NODE_H
#define AST_IF_NODE_H

#include "AstNode.h"

class AstNodeIf  :public AstNode {
protected:
    Ast *t1, *t2, *t3;    // if t1 then t2 else t3
public:
    AstNodeIf();
    AstNodeIf(const Ast& orig);
    bool inferer_types();
    void print();
    ~AstNodeIf();
};

#endif
