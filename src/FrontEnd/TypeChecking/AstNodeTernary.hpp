#ifndef AST_NODE_TERNARY_H
#define AST_NODE_TERNARY_H

#include "AstNode.hpp"


class AstNode ;

class AstNodeTernary : public AstNode {
protected:
    AstNode *t1, *t2, *t3 ;
public:
    AstNodeTernary(int class_code, AstNode *t1, AstNode *t2, AstNode *t3);
    void traversal(AstVisitor* vis) override;
    virtual ~AstNodeTernary() = 0 ;
};

class AstNodeIf : public AstNodeTernary {
public:
    Type * type = NULL ;
    AstNodeIf(AstNode *t1, AstNode *t2, AstNode *t3);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeIf();
};

class AstNodePut : public AstNodeTernary {
public:
    AstNodePut(AstNode *t1, AstNode *t2, AstNode *t3);
    void accept(AstVisAbstract* vis) override;
    ~AstNodePut();
};

#endif
