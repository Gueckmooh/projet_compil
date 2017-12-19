#ifndef AST_NODE_LEAF_H
#define AST_NODE_LEAF_H

#include "AstNode.hpp"
#include <list>
#include <string>

class AstNodeLeaf : public virtual AstNode {
public:
    AstNodeLeaf() ;
    void traversal(AstVisitor& vis) override;
    virtual ~AstNodeLeaf() = 0 ;
};

class AstNodeBool : public AstNodeLeaf {
protected:
    bool b;
public:
    AstNodeBool(bool b) ;
    std::ostream& print(std::ostream& os) override ;
    ~AstNodeBool() ;
};

class AstNodeFloat : public AstNodeLeaf {
protected:
    float f;
public:
    AstNodeFloat(float f) ;
    std::ostream& print(std::ostream& os) override ;
    ~AstNodeFloat() ;
};

class AstNodeInt : public AstNodeLeaf {
protected:
    int i;
public:
    AstNodeInt(int i) ;
    std::ostream& print(std::ostream& os) override ;
    ~AstNodeInt() ;
};

class AstNodeTuple : public AstNodeLeaf {
protected:
    std::list<AstNode *> var_list;
public:
    AstNodeTuple(std::list<AstNode *> var_list) ;
    void traversal(AstVisitor& vis) override;
    std::ostream& print(std::ostream& os) ;
    ~AstNodeTuple() ;
};

class AstNodeUnit : public AstNodeLeaf {
public:
    AstNodeUnit();
    ~AstNodeUnit() ;
};

class AstNodeVar : public AstNodeLeaf {
    std::string var_name ;
public:
    AstNodeVar(std::string var_name) ;
    std::ostream& print(std::ostream& os) override ;
    ~AstNodeVar() ;
};

#endif
