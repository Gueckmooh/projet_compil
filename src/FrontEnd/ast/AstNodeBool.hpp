
#ifndef AST_BOOL_NODE_H
#define AST_BOOL_NODE_H

#include "AstNodeLeaf.hpp"
#include "AstVisitor.hpp"

class AstNodeBool : public AstNodeLeaf {
protected:
    bool b;
public:
    AstNodeBool(bool b);
    ~AstNodeBool();

    bool infer_types();
    void print();
};

#endif
