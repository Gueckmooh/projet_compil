/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AstVisTypeChecking.hpp
 * Author: bap
 *
 * Created on 20 décembre 2017, 17:54
 */

#ifndef ASTVISTYPECHECKING_HPP
#define ASTVISTYPECHECKING_HPP

#include "AstVisitor.hpp"
#include "AstVis.hpp"
#include "Type.hpp"
#include "TypeFactory.hpp"
#include <map>
#include <set>

class AstVisPrint;

using std::string ;
using std::pair ;

typedef std::map<string, Type*> EnvironmentMap ;

class Environment {
private:
    std::ostream * os ;
    EnvironmentMap CM ;
    EnvironmentMap GM = {
        {"print_int", TypeFactory({TypeSimpleFactory(INT).create(), TypeSimpleFactory(UNIT).create()}).create()},
        {"+",  TypeFactory({TypeSimpleFactory(INT).create(), TypeSimpleFactory(INT).create(), TypeSimpleFactory(INT).create()}).create()},
        {"~-", TypeFactory({TypeSimpleFactory(INT).create(), TypeSimpleFactory(INT).create()}).create()}
    } ;
public:
    Environment();
    void setOs(std::ostream* os);
    EnvironmentMap getCurrent() const ;
    EnvironmentMap getGlobal() const ;
    Type * getVarType(string key) ;
    void addVar(string & key, Type * value) ;
    void removeVar(string & key) ;
    void printCurrent() ;
    virtual ~Environment();
};


class AstVisExplore : public AstVisPrint {
protected:
    Environment * Env ;
    void print(AstNode* node) ;
public:
    AstVisExplore(Environment * Env);
    void visit_node(AstNode* node) override;
    void visit_node(AstNodeInt* integer) override ;
    void visit_node(AstNodeNeg* neg) override;
    void visit_node(AstNodeVar* var) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeApp* app) override;
    void visit_node(AstNodeAdd* add) override;
    virtual ~AstVisExplore();
};

class AstVisRangeLet : public AstVisExplore {
    using AstVisExplore::AstVisExplore;
    void visit_node(AstNode* node) override;
    void visit_node(AstNodeInt* integer) override ;
    void visit_node(AstNodeNeg* neg) override;
    void visit_node(AstNodeVar* var) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeApp* app) override;
    void visit_node(AstNodeAdd* add) override;
    ~AstVisRangeLet();
};

class AstVisInfer : public AstVisPrint {
protected:
    Environment * Env ;
    AstNode * node ;
    Type * type ;
    void UnificationNode (AstNode *node, Type *type) ;
public:
    AstVisInfer(Environment * Env);
    virtual ~AstVisInfer() ;
    AstNode * getNode() const;
    void setNode(AstNode* node);
    Type* getType() const;
    void setType(Type* type);
    bool isWholeProgramCorrectlyTyped() ;
    void print(Type *type, AstNode* node) ;
    void visit_node(AstNode* node) override;
    void visit_node(AstNodeInt* integer) override;
    void visit_node(AstNodeNeg* neg) override;
    void visit_node(AstNodeVar* var) override;
    void visit_node(AstNodeLet* let) override ;
    void visit_node(AstNodeAdd* add) override;
    void visit_node(AstNodeApp* app) override;
};

#endif /* ASTVISTYPECHECKING_HPP */

