#include "AstNode.hpp"
#include "AstVisitor.hpp"

#ifndef AST_INT_NODE_H
#define AST_INT_NODE_H


class AstNodeInt : public AstNode {
protected:
    int i;
public:
    AstNodeInt(int i);
    ~AstNodeInt();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
