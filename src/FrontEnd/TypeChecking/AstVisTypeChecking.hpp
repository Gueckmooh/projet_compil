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
#include "type.h"
#include <map>
#include <list>

class AstVisPrint;

using std::string ;
using std::pair ;

typedef std::map<string, std::list<TCode>> EnvironmentMap ;

class Environment {
protected:
    EnvironmentMap EM = {
        {"print_int", {TY_INT, TY_UNIT}}
    } ;
    EnvironmentMap CE ;
public:
    Environment();
    EnvironmentMap getCurrent() const ;
    EnvironmentMap getGlobal() const ;
    virtual ~Environment();
private:

};


class AstVisExplore : public AstVisPrint {
protected:
    Environment * Env ;
    void print(AstNode* node) ;
    void print(AstNodeLet* let) ;
public:
    AstVisExplore(Environment * Env);
    void visit_node(AstNode* node) override;
    void visit_node(AstNodeInt* integer) override ;
    void visit_node(AstNodeVar* var) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeApp* app) override;
    void visit_node(AstNodeAdd* add) override;
    virtual ~AstVisExplore();
};

class AstVisInfer : public AstVisPrint {
protected:
    Environment * Env ;
    std::list<TCode> infer ;
    string value ;
public:
    AstVisInfer(Environment * Env);
    virtual ~AstVisInfer() ;
    std::list<TCode> getInfer() const;
    string getValue() const;
    void setValue(string value);
    void print(AstNode* node) ;
    void print(AstNodeLet* let) ;
    void visit_node(AstNode* node) override;
    void visit_node(AstNodeInt* integer) override;
    void visit_node(AstNodeVar* var) override;
    void visit_node(AstNodeLet* let) override ;
    void visit_node(AstNodeAdd* add) override;
    void visit_node(AstNodeApp* app) override;
    bool isCorrectlyTyped (AstNode* node) ;
};

#endif /* ASTVISTYPECHECKING_HPP */

