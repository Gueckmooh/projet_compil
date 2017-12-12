#ifndef AST_LET_NODE_H
#define AST_LET_NODE_H

#include "AstNode.h"
#include "Type.h"

class AstNodeLet  :public AstNode {
protected:
    Ast *t1, *t2;
    string var_name;
    Type type;
public:
    AstNodeLet();
    AstNodeLet(const Ast& orig);
    bool inferer_types();
    void print();
    ~AstNodeLet();
};

#endif
