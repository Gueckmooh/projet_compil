
#ifndef AST_LET_TUPLE_NODE_H
#define AST_LET_TUPLE_NODE_H

#include "AstNodeBinary.hpp"
#include <string>
#include <list>
#include "config.h"

class AstNodeLetTuple  :public AstNodeBinary {
protected:
    std::list<std::string> var_list;
public:
    AstNodeLetTuple(std::list<std::string> var_list, AstNode *t1, AstNode *t2);
    ~AstNodeLetTuple();

    bool infer_types();
    void print(int indent);
};

#endif
