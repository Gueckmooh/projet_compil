#include "AstNode.hpp"
#include "AstVisitor.hpp"

#include <string>
#include <list>

#ifndef AST_APP_NODE_H
#define AST_APP_NODE_H


class AstNodeApp  :public AstNode {
protected:
    std::list<std::string> args_list;
    AstNode *t1;
public:
    AstNodeApp(std::list<std::string> args_list, AstNode *t1);
    ~AstNodeApp();

    bool infer_types();
    void print();
    void traversal(AstVisitor *vis);
};

#endif
