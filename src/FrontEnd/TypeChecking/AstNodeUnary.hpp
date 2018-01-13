#ifndef AST_NODE_UNARY_H
#define AST_NODE_UNARY_H

#include "AstNodeLeaf.hpp"

class AstNode ;

class AstNodeUnary : public AstNode {
protected:
   AstNode * t1 ;
public:
    AstNodeUnary(int class_code, AstNode * t1);
    AstNode* getT1() const;
    void traversal(AstVisitor* vis) override;
    virtual ~AstNodeUnary() = 0 ;
};

class AstNodeApp : public AstNodeTuple {
protected :
    AstNodeVar *var ;
public:
    AstNodeApp(std::vector<AstNode *> args_list,AstNodeVar *var) ;
    AstNodeVar* getVar() const;
    void traversal(AstVisitor* vis) override;
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeApp() ;
};

class AstNodeFneg : public AstNodeUnary {
public:
    AstNodeFneg(AstNode *t1) ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFneg() ;
};

class AstNodeNeg : public AstNodeUnary {
public:
    AstNodeNeg(AstNode *t1) ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeNeg() ;
};

class AstNodeNot : public AstNodeUnary {
public:
    AstNodeNot(AstNode *t1) ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeNot() ;
};

class FunDef : public AstNodeUnary {
protected:
    AstNodeVar var ;
    std::vector<std::string> args_list ;
public:
    FunDef(std::string var_name, std::vector<std::string> args_list, AstNode *body);
    AstNodeVar & getVar();
    std::vector<std::string> & getArgs();
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    void traversal(AstVisitor* vis) override;
    ~FunDef();
};

class AstNodeLetRec : public AstNodeUnary {
    FunDef * fun_def ;
public:
    AstNodeLetRec(FunDef *fun_def, AstNode *t1);
    FunDef* getFunDef() const;
    void traversal(AstVisitor* vis) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeLetRec();
};


#endif
