#ifndef AST_NODE_LEAF_H
#define AST_NODE_LEAF_H

#include "AstNode.hpp"
#include "config.h"

#include <list>

/*
    Parent class : AstNodeLeaf
*/
class AstNodeLeaf : public AstNode{
public:
    AstNodeLeaf();
    ~AstNodeLeaf();

    void traversal(AstVisitor *vis);
};


/*
    Children classes of AstNodeLeaf
*/

//Bool
class AstNodeBool : public AstNodeLeaf {
protected:
    bool b;
public:
    AstNodeBool(bool b);
    ~AstNodeBool();

    bool infer_types();
    void print(int indent);
};

//Float
class AstNodeFloat : public AstNodeLeaf {
protected:
    float f;
public:
    AstNodeFloat(float f);
    ~AstNodeFloat();

    bool infer_types();
    void print(int indent);
};

//Int
class AstNodeInt : public AstNodeLeaf {
protected:
    int i;
public:
    AstNodeInt();
    AstNodeInt(int i);
    ~AstNodeInt();

    bool infer_types();
    void print(int indent);
};

//Tuple
class AstNodeTuple : public AstNodeLeaf {
protected:
    std::list<AstNode *> var_list;
public:
    AstNodeTuple(std::list<AstNode *> var_list);
    ~AstNodeTuple();

    bool infer_types();
    void print(int indent);
};

//Unit
class AstNodeUnit : public AstNodeLeaf {
public:
    AstNodeUnit();
    ~AstNodeUnit();

    bool infer_types();
    void print(int indent);
};

//Var
class AstNodeVar  :public AstNodeLeaf {
protected:
    std::string var_name;
public:
    AstNodeVar(std::string var_name);
    ~AstNodeVar();

    bool infer_types();
    void print(int indent);
};

#endif
