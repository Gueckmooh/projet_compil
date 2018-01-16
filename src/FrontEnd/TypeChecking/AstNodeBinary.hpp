#ifndef AST_NODE_BINARY_H
#define AST_NODE_BINARY_H

#include "AstNodeLeaf.hpp"

class AstNode ;
class FunDef ;

class AstNodeBinary : public AstNode {
protected:
    AstNode * t1, * t2 ;
public:
    AstNodeBinary(int class_code, AstNode *t1, AstNode *t2);
    AstNode* getT1() const;
    AstNode* getT2() const;
    void traversal(AstVisitor* vis) override;
    virtual ~AstNodeBinary() = 0 ;
};

class InfixOperator : public AstNodeBinary {
public:
    using AstNodeBinary::AstNodeBinary ;
    virtual ~InfixOperator() = 0 ;

};

class AstNodeAdd : public InfixOperator {
public:
    AstNodeAdd(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeAdd();
};

class AstNodeArray : public AstNodeBinary {
public:
    AstNodeArray(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeArray();
};

class AstNodeEq : public InfixOperator {
public:
    AstNodeEq(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeEq();
};

class AstNodeFadd : public InfixOperator {
public:
    AstNodeFadd(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFadd();
};

class AstNodeFdiv : public InfixOperator {
public:
    AstNodeFdiv(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFdiv();
};

class AstNodeFmul : public InfixOperator {
public:
    AstNodeFmul(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFmul();
};

class AstNodeFsub : public InfixOperator {
public:
    AstNodeFsub(AstNode * t1, AstNode * t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFsub();
};

class AstNodeGet : public AstNodeBinary {
public:
    AstNodeGet(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeGet();
};

class AstNodeLe : public InfixOperator {
public:
    AstNodeLe(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeLe();
};

class AstNodeLet : public AstNodeBinary {
    AstNodeVar var ;
public:
    AstNodeLet(AstNode *t1, AstNode *t2, std::string var_name);
    AstNodeVar getVar() const;
    void traversal(AstVisitor* vis) override;
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeLet();
};

class AstNodeLetTuple : public AstNodeBinary {
protected:
    std::vector<std::string> var_list ;
public:
    AstNodeLetTuple(std::vector<std::string> var_list, AstNode *t1, AstNode *t2);
    std::vector<std::string> & getVar_list() ;
    void traversal(AstVisitor* vis) override;
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeLetTuple();
};

class AstNodeSub : public InfixOperator {
public:
    AstNodeSub(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeSub();
};

#endif
