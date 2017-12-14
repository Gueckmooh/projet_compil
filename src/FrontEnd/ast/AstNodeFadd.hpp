
#ifndef AST_Fadd_NODE_H
#define AST_Fadd_NODE_H

#include "AstNode.hpp"
#include "AstVisitor.hpp"

class AstNodeFadd : public AstNode {
protected:
    AstNode *t1;
    AstNode *t2;
public:
    AstNodeFadd(AstNode *t1, AstNode *t2);
    ~AstNodeFadd();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
