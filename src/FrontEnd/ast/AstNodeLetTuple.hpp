#include "AstNode.hpp"
#include <string>
#include <list>

#ifndef AST_LET_TUPLE_NODE_H
#define AST_LET_TUPLE_NODE_H


class AstNodeLetTuple  :public AstNode {
protected:
    std::list<std::string> var_list;
    AstNode *t1, *t2;
public:
    AstNodeLetTuple(std::list<std::string> var_list, AstNode *t1, AstNode *t2);
    ~AstNodeLetTuple();

    bool infer_types();
    void print();
};

#endif
