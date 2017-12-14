
#ifndef AST_LE_NODE_H
#define AST_LE_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"

class AstNodeLe  :public AstNodeBinary {
public:
    AstNodeLe(AstNode *t1, AstNode *t2);
    ~AstNodeLe();

    bool infer_types();
    void print();
};

#endif
