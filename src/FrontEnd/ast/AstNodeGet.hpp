
#ifndef AST_GET_NODE_H
#define AST_GET_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

class AstNodeGet  :public AstNodeBinary {
public:
    AstNodeGet(AstNode *t1, AstNode *t2);
    ~AstNodeGet();

    bool infer_types();
    void print(int indent);
};

#endif
