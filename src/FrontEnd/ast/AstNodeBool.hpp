
#ifndef AST_BOOL_NODE_H
#define AST_BOOL_NODE_H

#include "AstNodeLeaf.hpp"
#include "AstVisitor.hpp"
#include "config.h"

class AstNodeBool : public AstNodeLeaf {
protected:
    bool b;
public:
    AstNodeBool(bool b);
    ~AstNodeBool();

    bool infer_types();
    void print(int indent);
};

#endif
