#ifndef AST_BOOL_NODE_H
#define AST_BOOL_NODE_H

#include "AstNode.h"

class AstNodeBool  :public AstNode {
protected:
    bool b;
public:
    AstNodeBool();
    AstNodeBool(const Ast& orig);
    bool inferer_types();
    void print();
    ~AstNodeBool();
};

#endif
