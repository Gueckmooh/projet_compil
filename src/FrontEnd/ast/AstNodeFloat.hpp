#include "AstNode.hpp"
#include "AstVisitor.hpp"

#ifndef AST_FLOAT_NODE_H
#define AST_FLOAT_NODE_H


class AstNodeFloat : public AstNode {
protected:
    float f;
public:
    AstNodeFloat(float f);
    ~AstNodeFloat();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
