#ifndef AST_FLOAT_NODE_H
#define AST_FLOAT_NODE_H

#include "AstNode.h"

class AstNodeFloat  :public AstNode {
protected:
    float f;
public:
    AstNodeFloat();
    AstNodeFloat(const Ast& orig);
    bool inferer_types();
    void print();
    ~AstNodeFloat();
};

#endif
