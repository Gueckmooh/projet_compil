#include "AstNode.hpp"
#include "AstVisitor.hpp"

#ifndef AST_BOOL_NODE_H
#define AST_BOOL_NODE_H


class AstNodeBool : public AstNode {
protected:
    bool b;
public:
    AstNodeBool(bool b);
    ~AstNodeBool();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
