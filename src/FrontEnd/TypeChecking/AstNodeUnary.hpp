#ifndef AST_NODE_UNARY_H
#define AST_NODE_UNARY_H

#include "Type.hpp"
#include "AstNodeLeaf.hpp"

class AstNode ;

class AstNodeUnary : public virtual AstNode {
protected:
   AstNode * t1 ;
public:
    AstNodeUnary(AstNode *t1);
    void traversal(AstVisitor& vis) override;
    virtual ~AstNodeUnary() = 0 ;
};

class AstNodeApp : public AstNodeTuple, public AstNodeUnary {
public:
    AstNodeApp(std::list<AstNode *> args_list,AstNode *t1) ;
    void traversal(AstVisitor& vis) override;
    std::ostream& print(std::ostream& os) override;
    ~AstNodeApp() ;
};

class AstNodeFneg : public AstNodeUnary {
public:
    AstNodeFneg(AstNode *t1) ;
    ~AstNodeFneg() ;
};

class AstNodeNeg : public AstNodeUnary {
public:
    AstNodeNeg(AstNode *t1) ;
    ~AstNodeNeg() ;
};

class AstNodeNot : public AstNodeUnary {
public:
    AstNodeNot(AstNode *t1) ;  
    ~AstNodeNot() ;
};

class FunDef : public AstNodeVar, public AstNodeUnary {
protected:
    std::list<std::string> args_list ;
public:
    FunDef(std::string var_name, TCode tc, std::list<std::string> args_list, AstNode *body);
    std::ostream& print(std::ostream& os) override;
    void traversal(AstVisitor& vis) override;
    ~FunDef();
};

class AstNodeLetRec : public AstNodeUnary {
    FunDef * fun_def ;
public:
    AstNodeLetRec(FunDef *fun_def, AstNode *t1);
    void traversal(AstVisitor& vis) override;
    ~AstNodeLetRec();
};


#endif