
#ifndef AST_INT_NODE_H
#define AST_INT_NODE_H

#include "AstNodeUnary.hpp"
#include "AstVisitor.hpp"

class AstNodeInt : public AstNodeUnary {
protected:
    int i;
public:
    AstNodeInt();
    AstNodeInt(int i);
    ~AstNodeInt();

    bool infer_types();
    void print();
};

#endif
