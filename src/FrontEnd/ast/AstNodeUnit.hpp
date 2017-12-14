#include "AstNode.hpp"

#ifndef AST_UNIT_NODE_H
#define AST_UNIT_NODE_H


class AstNodeUnit : public AstNode {
public:
    AstNodeUnit();
    ~AstNodeUnit();

    bool infer_types();
    void print();
};

#endif
