#ifndef AST_NODE_UNARY_H
#define AST_NODE_UNARY_H

#include "AstNode.hpp"
#include "config.h"

#include <list>


/*
    Parent class : AstNodeUnary
*/
class AstNodeUnary : public AstNode{
protected:
    AstNode *t1;
public:
    AstNodeUnary();
    AstNodeUnary(AstNode *t1);
    ~AstNodeUnary();

    virtual void traversal(AstVisitor *vis);
};

/*
    Children classes of AstNodeUnary
*/

//App
class AstNodeApp : public AstNodeUnary {
protected:
    std::list<AstNode *> args_list;
public:
    AstNodeApp(std::list<AstNode *> args_list, AstNode *t1);
    ~AstNodeApp();

    bool infer_types();
    void print(int indent);
    void traversal(AstVisitor *vis);
};

//Fneg
class AstNodeFneg : public AstNodeUnary {
public:
    AstNodeFneg(AstNode *t1);
    ~AstNodeFneg();

    bool infer_types();
    void print(int indent);
};

//Neg
class AstNodeNeg : public AstNodeUnary {
public:
    AstNodeNeg(AstNode *t1);
    ~AstNodeNeg();

    bool infer_types();
    void print(int indent);
};

//Not
class AstNodeNot : public AstNodeUnary {
public:
    AstNodeNot(AstNode *t1);
    ~AstNodeNot();

    bool infer_types();
    void print(int indent);
};

#endif
