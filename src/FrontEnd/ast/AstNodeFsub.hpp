
#ifndef AST_FSUB_NODE_H
#define AST_FSUB_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "AstNode.hpp"

class AstNodeFsub : public AstNodeBinary {
public:
    AstNodeFsub(AstNode *t1, AstNode *t2);
    ~AstNodeFsub();

    bool infer_types();
    void print();
};

#endif
