
#ifndef AST_FDIV_NODE_H
#define AST_FDIV_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"

class AstNodeFdiv : public AstNodeBinary {
public:
    AstNodeFdiv(AstNode *t1, AstNode *t2);
    ~AstNodeFdiv();

    bool infer_types();
    void print();
};

#endif
