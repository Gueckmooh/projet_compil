/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Environment.cpp
 * Author: bap
 * 
 * Created on 20 décembre 2017, 17:54
 */

#include "AstNode.hpp"
#include "AstNodeLeaf.hpp"
#include "AstNodeUnary.hpp"
#include "AstNodeBinary.hpp"
#include "AstVisTypeChecking.hpp"
#include "Strategy.hpp"
#include <sstream>
#include <cassert>


Environment::Environment() {}

EnvironmentMap Environment::getCurrent() const {
    return CE ;
}

EnvironmentMap Environment::getGlobal() const {
    return EM ;
}


Environment::~Environment() {
}

AstVisExplore::AstVisExplore(Environment * Env) : 
AstVisPrint(), Env(Env)  {
}

void AstVisExplore::print(AstNode* node) {
    getAstVis()->getOs() << " : Rien à ajouter dans l'environnement\n" ;
}

void AstVisExplore::print(AstNodeLet* let) {
    getAstVis()->getOs() << " : On ajoute la variable " << *let << " dans l'environnement courant : " ;
    getAstVis()->getOs() << let->TCode_to_string(let->getType()) << " = " << let->getValue() << std::endl ;
}

void AstVisExplore::visit_node(AstNode* node) {
    AstVisPrint::print(node) ;
    print(node) ;
}

void AstVisExplore::visit_node(AstNodeInt* integer) {
    AstVisPrint::print(integer) ;
    print(integer) ;
}

void AstVisExplore::visit_node(AstNodeVar* var) {
    AstVisPrint::print(var) ;
    print(var) ;
    /*EnvironmentMap::iterator it = Env->getCurrent().find(var->getVar_name()) ;
    getAstVis()->getOs() << it->first + "\n" ;
    if (it != Env->getCurrent().end()) {
        getAstVis()->getOs() << string(" : la variable " + var->getVar_name() + " est présente dans l'environnement courant : ")  ;
        var->setTcval(it->second);
    }
    it = Env->getGlobal().find(var->getVar_name()) ;
    if (it != Env->getGlobal().end()) {
        getAstVis()->getOs() << string(" : la variable " + var->getVar_name() + " est présente dans l'environnement courant : ")  ;
        var->setTcval(it->second) ;
    }
    else
        assert(false) ;*/
    
}

void AstVisExplore::visit_node(AstNodeLet* let) {
    getAstVis()->getOs() << "On infère la valeur de " << let->getVar_name() << " : \n" ;
    let->setTc(TY_VAR) ;
    AstVisitor * TypeChecker = Strategy(Strategy::V_TYPE_CHECKER).setupAstVisitor() ;
    let->getT1()->apply(TypeChecker) ;
    AstVisInfer * vis = (AstVisInfer *)TypeChecker->getFeedBack() ;
    let->setTcval(vis->getInfer()) ;
    let->setValue(vis->getValue()) ;
    delete TypeChecker ;
    AstVisPrint::print(let) ;
    print(let) ;
    /*std::pair<string,std::list<TCode>> p = std::pair<string,std::list<TCode>>(let->getVar_name(), let->getTcval()) ;
    getAstVis()->getOs() << "Variable insérée : " << (Env->getCurrent().insert(p)).first->first << "\n";
    getAstVis()->getOs() << Env->getCurrent().find(let->getVar_name())->first << "\n" ;*/
}

void AstVisExplore::visit_node(AstNodeApp* app) {
    getAstVis()->getOs() << "On infère la valeur de l'application " << *app << " : \n" ;
    app->setTc(TY_VAR) ;
    AstVisitor * TypeChecker = Strategy(Strategy::V_TYPE_CHECKER).setupAstVisitor() ;
    app->getT1()->apply(TypeChecker) ;
    for (auto node : app->getVar_list()) {
        node->apply(TypeChecker) ;
    }

    //AstVisInfer * vis = (AstVisInfer *)inferator->getFeedBack() ;
    //app->setTcval(vis->getInfer()) ;
    //app->setValue(vis->getValue()) ;
    delete TypeChecker ;
    AstVisPrint::print(app) ;
    print(app) ;
}

void AstVisExplore::visit_node(AstNodeAdd* add) {
    /*getAstVis()->getOs() << "On infère la valeur de l'application " << *app << " : \n" ;
    app->setTc(TY_VAR) ;
    AstVisitor * inferator = Strategy(Strategy::V_INFERATOR, Env).setupAstVisitor() ;
    app->apply(inferator) ;*/
    AstVisPrint::print(add) ;
    print(add) ;
}


AstVisExplore::~AstVisExplore() {
}

AstVisInfer::AstVisInfer(Environment * Env) :
AstVisPrint(), Env(Env), value(string())  {
}

string AstVisInfer::getValue() const {
    return value;
}

void AstVisInfer::setValue(string value) {
    this->value = value;
}

std::list<TCode> AstVisInfer::getInfer() const {
    return infer ;
}

AstVisInfer::~AstVisInfer() {}

void AstVisInfer::print(AstNode* node) {
    getAstVis()->getOs() << string(" - : ") << node->TCode_to_string(node->getType()) << string(" = ") << *node << std::endl ; 
}

void AstVisInfer::print(AstNodeLet* let) {
    getAstVis()->getOs() << string(": On retire la variable de l'environnement courant : ") << let->TCode_to_string(let->getType()) << std::endl ;
}

void AstVisInfer::visit_node(AstNode* node) {
    AstVisPrint::print(node) ;
    print(node) ; 
}

void AstVisInfer::visit_node(AstNodeInt* integer) {
    AstVisPrint::print(integer) ;
    print(integer) ;
    infer.push_back(integer->getType()) ;
    std::stringstream ss ;
    ss << *integer ;
    value = ss.str()  ;
}

void AstVisInfer::visit_node(AstNodeVar* var) {
    AstVisPrint::print(var) ;
    print(var) ;
}

void AstVisInfer::visit_node(AstNodeLet* let) {
    AstVisPrint::print(let) ;
    print(let) ;
    //Env->getCurrent().erase(let->getVar_name()) ;  
}

void AstVisInfer::visit_node(AstNodeApp* app) {
    AstVisPrint::print(app) ;
    print(app) ;
}

void AstVisInfer::visit_node(AstNodeAdd* add) {
    AstVisPrint::print(add) ;
    print(add) ;
}

bool AstVisInfer::isCorrectlyTyped(AstNode* node) {
    return true ;
}