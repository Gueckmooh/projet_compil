
#ifndef AST_VAR_NODE_H
#define AST_VAR_NODE_H

#include <string>
#include "AstNodeLeaf.hpp"
#include "config.h"

class AstNodeVar  :public AstNodeLeaf {
protected:
    std::string var_name;
public:
    AstNodeVar(std::string var_name);
    ~AstNodeVar();

    bool infer_types();
    void print(int indent);
};

#endif
