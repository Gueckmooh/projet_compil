#ifndef AST_NODE_LEAF_H
#define AST_NODE_LEAF_H

#include "AstNode.hpp"
#include "AstVisitor.hpp"
#include "AstVis.hpp"
#include <vector>
#include <string>

class AstVisAbstract;
class AstNode ;

class AstNodeLeaf : public AstNode {
public:
    AstNodeLeaf(int class_code) ;
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
    std::vector<AstNode *> var_list;
public:
    AstNodeTuple(std::vector<AstNode *> var_list) ;
    std::vector<AstNode*> getVar_list() const;
    void traversal(AstVisitor* vis) override;
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeTuple() ;
};

class AstNodeUnit : public AstNodeLeaf {
public:
    AstNodeUnit();
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeUnit() ;
};

class AstNodeVar : public AstNodeLeaf {
protected:
    std::string var_name ;
public:
    AstNodeVar(std::string var_name) ;
    std::string & getVar_name() ;
    std::ostream& print(std::ostream& os) override ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeVar() ;
};

#endif
