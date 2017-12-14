
#ifndef AST_NODE_H
#define	AST_NODE_H

#include <string>
#include "ast.h"


class AstNode {
public:
    virtual bool infer_types() = 0;
    virtual void print() = 0;
    ~AstNode() {};
};

AstNode* build_ast(ptree tree);

#endif	/* AST_H */
