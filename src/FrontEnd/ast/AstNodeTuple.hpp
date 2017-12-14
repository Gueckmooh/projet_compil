#include "AstNode.hpp"

#include <string>
#include <list>

#ifndef AST_TUPLE_NODE_H
#define AST_TUPLE_NODE_H


class AstNodeTuple  :public AstNode {
protected:
    std::list<std::string> var_list;
public:
    AstNodeTuple(std::list<std::string> var_list);
    ~AstNodeTuple();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
