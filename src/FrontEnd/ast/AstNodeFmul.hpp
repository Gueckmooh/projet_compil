
#ifndef AST_FMUL_NODE_H
#define AST_FMUL_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

class AstNodeFmul : public AstNodeBinary {
public:
    AstNodeFmul(AstNode *t1, AstNode *t2);
    ~AstNodeFmul();

    bool infer_types();
    void print(int indent);
};

#endif
