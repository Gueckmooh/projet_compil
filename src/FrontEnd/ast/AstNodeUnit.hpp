
#ifndef AST_UNIT_NODE_H
#define AST_UNIT_NODE_H

#include "AstNodeLeaf.hpp"
#include "config.h"

class AstNodeUnit : public AstNodeLeaf {
public:
    AstNodeUnit();
    ~AstNodeUnit();

    bool infer_types();
    void print(int indent);
};

#endif
