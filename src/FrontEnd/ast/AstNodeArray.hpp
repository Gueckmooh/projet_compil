
#ifndef AST_ARRAY_NODE_H
#define AST_ARRAY_NODE_H

#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

class AstNodeArray : public AstNodeBinary {
public:
    AstNodeArray(AstNode *t1, AstNode *t2);
    ~AstNodeArray();

    bool infer_types();
    void print(int indent);
};

#endif
