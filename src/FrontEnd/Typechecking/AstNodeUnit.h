#ifndef AST_UNIT_NODE_H
#define AST_UNIT_NODE_H

#include "AstNode.h"

class AstNodeUnit  :public AstNode {
public:
    AstNodeUnit();
    AstNodeUnit(const Ast& orig);
    bool inferer_types();
    void print();
    ~AstNodeUnit();
};

#endif
