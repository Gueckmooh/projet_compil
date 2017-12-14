
#ifndef AST_UNIT_NODE_H
#define AST_UNIT_NODE_H

#include "AstNodeLeaf.hpp"

class AstNodeUnit : public AstNodeLeaf {
public:
    AstNodeUnit();
    ~AstNodeUnit();

    bool infer_types();
    void print();
};

#endif
