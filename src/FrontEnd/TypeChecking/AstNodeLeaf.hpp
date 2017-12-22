#ifndef AST_NODE_LEAF_H
#define AST_NODE_LEAF_H

#include "AstNode.hpp"
#include "AstVisitor.hpp"
#include "AstVis.hpp"
#include <list>
#include <string>

class AstVisAbstract;
class AstNode ;

class AstNodeLeaf : public virtual AstNode {
public:
    AstNodeLeaf() ;
    void traversal(AstVisitor* vis) override;
    virtual ~AstNodeLeaf() = 0 ;
};

class AstNodeBool : public AstNodeLeaf {
protected:
    bool b;
public:
    AstNodeBool(bool b) ;
    std::ostream& print(std::ostream& os) override ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeBool() ;
};

class AstNodeFloat : public AstNodeLeaf {
protected:
    float f;
public:
    AstNodeFloat(float f) ;
    std::ostream& print(std::ostream& os) override ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFloat() ;
};

class AstNodeInt : public AstNodeLeaf {
protected:
    int i;
public:
    AstNodeInt(int i) ;
    std::ostream& print(std::ostream& os) override ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeInt() ;
};

class AstNodeTuple : public AstNodeLeaf {
protected:
    std::list<AstNode *> var_list;
public:
    AstNodeTuple(std::list<AstNode *> var_list) ;
    std::list<AstNode*> getVar_list() const;
    void traversal(AstVisitor* vis) override;
    std::ostream& print(std::ostream& os) ;
    std::string printType() override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeTuple() ;
};

class AstNodeUnit : public AstNodeLeaf {
public:
    AstNodeUnit();
    void accept(AstVisAbstract* vis) override;
    ~AstNodeUnit() ;
};

class AstNodeVar : public AstNodeLeaf {
protected:
    std::string var_name ;
    std::list<TCode> tcval ;
public:
    AstNodeVar(std::string var_name) ;
    std::string printType() override;
    std::string  getVar_name() ;
    std::list<TCode> getTcval() const;
    void setTcval(std::list<TCode> tcval);
    std::ostream& print(std::ostream& os) override ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeVar() ;
};

#endif
