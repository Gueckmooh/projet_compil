#include <string>
#include "ast.h"
#include "AstVisitor.hpp"

#ifndef AST_NODE_H
#define	AST_NODE_H

class AstVisitor;

class AstNode {
public:
    ~AstNode() {};

    virtual bool infer_types() = 0;
    virtual void print() = 0;
    virtual void traversal(AstVisitor *vis) = 0;
};

AstNode* build_ast(ptree tree);

#endif	/* AST_H */
