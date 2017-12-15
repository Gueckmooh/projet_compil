#ifndef AST_NODE_BINARY_H
#define AST_NODE_BINARY_H

#include "AstNode.hpp"
#include "config.h"
#include "AstVisitor.hpp"
#include "Type.hpp"

#include <list>
/*
    Parent class : AstNodeBinary
*/

class AstNodeBinary : public AstNode{
protected:
    AstNode *t1, *t2;
public:
    AstNodeBinary();
    AstNodeBinary(AstNode *t1, AstNode *t2);
    ~AstNodeBinary();

    void print(int indent);
    void traversal(AstVisitor *vis);
};


/*
    Children classes of AstNodeBinary
*/

//Add
class AstNodeAdd : public AstNodeBinary {
public:
    AstNodeAdd(AstNode *t1, AstNode *t2);
    ~AstNodeAdd();

    bool infer_types();
    void print(int indent);
};

//Array
class AstNodeArray : public AstNodeBinary {
public:
    AstNodeArray(AstNode *t1, AstNode *t2);
    ~AstNodeArray();

    bool infer_types();
    void print(int indent);
};

//Eq
class AstNodeEq  :public AstNodeBinary {
public:
    AstNodeEq(AstNode *t1, AstNode *t2);
    ~AstNodeEq();

    bool infer_types();
    void print(int indent);
};

//Fadd
class AstNodeFadd : public AstNodeBinary {
public:
    AstNodeFadd(AstNode *t1, AstNode *t2);
    ~AstNodeFadd();

    bool infer_types();
    void print(int indent);
};

//Fdiv
class AstNodeFdiv : public AstNodeBinary {
public:
    AstNodeFdiv(AstNode *t1, AstNode *t2);
    ~AstNodeFdiv();

    bool infer_types();
    void print(int indent);
};

//Fmul
class AstNodeFmul : public AstNodeBinary {
public:
    AstNodeFmul(AstNode *t1, AstNode *t2);
    ~AstNodeFmul();

    bool infer_types();
    void print(int indent);
};

//Fsub
class AstNodeFsub : public AstNodeBinary {
public:
    AstNodeFsub(AstNode *t1, AstNode *t2);
    ~AstNodeFsub();

    bool infer_types();
    void print(int indent);
};

//Get
class AstNodeGet  :public AstNodeBinary {
public:
    AstNodeGet(AstNode *t1, AstNode *t2);
    ~AstNodeGet();

    bool infer_types();
    void print(int indent);
};

//Le
class AstNodeLe  :public AstNodeBinary {
public:
    AstNodeLe(AstNode *t1, AstNode *t2);
    ~AstNodeLe();

    bool infer_types();
    void print(int indent);
};

//Let
class AstNodeLet : public AstNodeBinary {
protected:
    std::string var_name;
    Type type;
public:
    AstNodeLet(AstNode *t1, AstNode *t2, std::string var_name);
    ~AstNodeLet();

    bool infer_types();
    void print(int indent);
};

//Sub
class AstNodeSub : public AstNodeBinary {
public:
    AstNodeSub(AstNode *t1, AstNode *t2);
    ~AstNodeSub();

    bool infer_types();
    void print(int indent);
};

//Tuple
class AstNodeLetTuple  :public AstNodeBinary {
protected:
    std::list<AstNode *> var_list;
public:
    AstNodeLetTuple(std::list<AstNode *> var_list, AstNode *t1, AstNode *t2);
    ~AstNodeLetTuple();

    bool infer_types();
    void print(int indent);
};

#endif
