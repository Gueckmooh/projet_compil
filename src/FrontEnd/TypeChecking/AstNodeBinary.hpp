#ifndef AST_NODE_BINARY_H
#define AST_NODE_BINARY_H

#include "Type.hpp"
#include "AstNodeLeaf.hpp"

class AstNode ;
class FunDef ;

class AstNodeBinary : public virtual AstNode {
protected:
    AstNode * t1, * t2 ;
public:
    AstNodeBinary(AstNode *t1, AstNode *t2);
    void traversal(AstVisitor& vis) override;
    virtual ~AstNodeBinary() = 0 ;
};

class AstNodeAdd : public AstNodeBinary {
public:
    AstNodeAdd(AstNode *t1, AstNode *t2);
    ~AstNodeAdd();
};

class AstNodeArray : public AstNodeBinary {
public:
    AstNodeArray(AstNode *t1, AstNode *t2);
    ~AstNodeArray();
};

class AstNodeEq : public AstNodeBinary {
public:
    AstNodeEq(AstNode *t1, AstNode *t2);
    ~AstNodeEq();
};

class AstNodeFadd : public AstNodeBinary {
public:
    AstNodeFadd(AstNode *t1, AstNode *t2);
    ~AstNodeFadd();
};

class AstNodeFdiv : public AstNodeBinary {
public:
    AstNodeFdiv(AstNode *t1, AstNode *t2);
    ~AstNodeFdiv();
};

class AstNodeFmul : public AstNodeBinary {
public:
    AstNodeFmul(AstNode *t1, AstNode *t2);
    ~AstNodeFmul();
};

class AstNodeFsub : public AstNodeBinary {
public:
    AstNodeFsub(AstNode * t1, AstNode * t2);
    ~AstNodeFsub();
};

class AstNodeGet : public AstNodeBinary {
public:
    AstNodeGet(AstNode *t1, AstNode *t2);
    ~AstNodeGet();
};

class AstNodeLe : public AstNodeBinary {
public:
    AstNodeLe(AstNode *t1, AstNode *t2);
    ~AstNodeLe();
};

class AstNodeLet : public AstNodeBinary {
public:
    AstNodeLet(AstNode *t1, AstNode *t2, std::string var_name);
    void traversal(AstVisitor& vis) override;
    std::ostream& print(std::ostream& os) override;
    ~AstNodeLet();
};

class AstNodeLetTuple : public AstNodeBinary {
protected:
    std::list<std::string> var_list ;
public:
    AstNodeLetTuple(std::list<std::string> var_list, AstNode *t1, AstNode *t2);
    void traversal(AstVisitor& vis) override;
    std::ostream& print(std::ostream& os) override;
    ~AstNodeLetTuple();
};

class AstNodeSub : public AstNodeBinary {
public:
    AstNodeSub(AstNode *t1, AstNode *t2);
    ~AstNodeSub();
};

#endif
