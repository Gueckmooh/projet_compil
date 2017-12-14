
#ifndef AST_GET_NODE_H
#define AST_GET_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"

class AstNodeGet  :public AstNodeBinary {
public:
    AstNodeGet(AstNode *t1, AstNode *t2);
    ~AstNodeGet();

    bool infer_types();
    void print();
};

#endif
