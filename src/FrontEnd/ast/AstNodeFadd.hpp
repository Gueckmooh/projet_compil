
#ifndef AST_Fadd_NODE_H
#define AST_Fadd_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

class AstNodeFadd : public AstNodeBinary {
public:
    AstNodeFadd(AstNode *t1, AstNode *t2);
    ~AstNodeFadd();

    bool infer_types();
    void print(int indent);
};

#endif
