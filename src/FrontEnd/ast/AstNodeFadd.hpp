
#ifndef AST_Fadd_NODE_H
#define AST_Fadd_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"

class AstNodeFadd : public AstNodeBinary {
public:
    AstNodeFadd(AstNode *t1, AstNode *t2);
    ~AstNodeFadd();

    bool infer_types();
    void print();
};

#endif
