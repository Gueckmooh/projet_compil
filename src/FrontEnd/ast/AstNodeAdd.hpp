
#ifndef AST_ADD_NODE_H
#define AST_ADD_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

class AstNodeAdd : public AstNodeBinary {
public:
    AstNodeAdd(AstNode *t1, AstNode *t2);
    ~AstNodeAdd();

    bool infer_types();
    void print(int indent);
};

#endif
