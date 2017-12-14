
#ifndef AST_TUPLE_NODE_H
#define AST_TUPLE_NODE_H

#include "AstNodeLeaf.hpp"
#include <string>
#include <list>

class AstNodeTuple : public AstNodeLeaf {
protected:
    std::list<std::string> var_list;
public:
    AstNodeTuple(std::list<std::string> var_list);
    ~AstNodeTuple();

    bool infer_types();
    void print();
};

#endif
