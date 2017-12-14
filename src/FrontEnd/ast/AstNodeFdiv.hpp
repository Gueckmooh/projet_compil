
#ifndef AST_FDIV_NODE_H
#define AST_FDIV_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

class AstNodeFdiv : public AstNodeBinary {
public:
    AstNodeFdiv(AstNode *t1, AstNode *t2);
    ~AstNodeFdiv();

    bool infer_types();
    void print(int indent);
};

#endif
