
#ifndef AST_FLOAT_NODE_H
#define AST_FLOAT_NODE_H

#include "AstNodeLeaf.hpp"
#include "AstVisitor.hpp"
#include "config.h"

class AstNodeFloat : public AstNodeLeaf {
protected:
    float f;
public:
    AstNodeFloat(float f);
    ~AstNodeFloat();

    bool infer_types();
    void print(int indent);
};

#endif
