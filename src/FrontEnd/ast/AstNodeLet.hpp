
#ifndef AST_LET_NODE_H
#define AST_LET_NODE_H

#include "AstNode.hpp"
#include "Type.hpp"
#include <string>

class AstNodeLet : public AstNode {
protected:
    AstNode *t1, *t2;
    std::string var_name;
    Type type;
public:
    AstNodeLet(AstNode *t1, AstNode *t2, std::string var_name);
    ~AstNodeLet();

    bool infer_types();
    void print();
};

#endif
