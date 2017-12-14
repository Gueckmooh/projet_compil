
#ifndef AST_APP_NODE_H
#define AST_APP_NODE_H

#include "AstNodeUnary.hpp"
#include "AstVisitor.hpp"

#include <string>
#include <list>

class AstNodeApp : public AstNodeUnary {
protected:
    std::list<std::string> args_list;
public:
    AstNodeApp(std::list<std::string> args_list, AstNode *t1);
    ~AstNodeApp();

    bool infer_types();
    void print();
};

#endif
