#include <string>
#include "AstNode.hpp"

#ifndef AST_VAR_NODE_H
#define AST_VAR_NODE_H

class AstNodeVar  :public AstNode {
protected:
    std::string var_name;
public:
    AstNodeVar(std::string var_name);
    ~AstNodeVar();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
