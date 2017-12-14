
#ifndef AST_LET_NODE_H
#define AST_LET_NODE_H

#include "AstNodeBinary.hpp"
#include "Type.hpp"
#include <string>

class AstNodeLet : public AstNodeBinary {
protected:
    std::string var_name;
    Type type;
public:
    AstNodeLet(AstNode *t1, AstNode *t2, std::string var_name);
    ~AstNodeLet();

    bool infer_types();
    void print();
};

#endif
