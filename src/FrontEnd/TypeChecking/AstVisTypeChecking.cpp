/*
type classe mere: simple -> classe fille ou complexe_fleche ou complexe_croix classes fille
si simple : int, float , ...
si complexe : *type1, *type2 (represente type1 -> type2)

print_cplex(type T){
    print"("
    print_type(T->type1)
    print") -> ("
    print_type(t->type2)
    print")"
}
f (type g) -> (type h)
f x y z t
X->(Y->(Z->T))
 
 
mke_type(list args ){
    if (len args == 1){
	return type(args[1]) // constructeur Type(Type T)
    }
    type 1 = args[1]; // constructuer Type(Type T)
    args -> eneleve 1er element
    type2 = mke_type(args);
    return type(type1, type2) // constructeur (Type t1, Type T2)
}
*/

#include "AstNode.hpp"
#include "AstNodeLeaf.hpp"
#include "AstNodeUnary.hpp"
#include "AstNodeBinary.hpp"
#include "AstVisTypeChecking.hpp"
#include "Strategy.hpp"
#include <cassert>
#include <iostream>

Environment::Environment() : os(NULL) {
}

void Environment::setOs(std::ostream* os) {
    this->os = os;
}

EnvironmentMap Environment::getCurrent() const {
    return CM ;
}

EnvironmentMap Environment::getGlobal() const {
    return GM ;
}

Type* Environment::getVarType(string key) {
    EnvironmentMap::iterator it = CM.find(key) ;
    if (it != CM.end())
        return it->second ;
    it = GM.find(key) ;
    if (it != GM.end())
        return it->second ;
    assert(false) ;
}

void Environment::addVar(string & key, Type* value) {
    CM[key] = value ;
}

void Environment::removeVar(string & key) {
    EnvironmentMap::iterator it = CM.find(key) ;
    Type::deleteTypeRec(it->second) ;
    CM.erase(it) ;
}

Environment::~Environment() {
    for (auto pair : CM)
        Type::deleteTypeRec(pair.second) ;
    for (auto pair : GM)
        Type::deleteTypeRec(pair.second) ;
}


void Environment::printCurrent() {
    *os << "Current Environment : [" ;
    EnvironmentMap::iterator it = CM.begin() ;
    if (it != CM.end()) {
        *os << it->first << " : " << *it->second ;
        it++ ;
    }
    
    for (; it != CM.end() ; it++)
        *os << ", " << it->first << " : " << *it->second ;
    *os << "]" ;
}

AstVisExplore::AstVisExplore(Environment * Env) : 
AstVisPrint(), Env(Env)  {
}

void AstVisExplore::print(AstNode* node) {
    getAstVis()->getOs() << " : Rien à ajouter dans l'environnement\n" ;
}

void AstVisExplore::visit_node(AstNode* node) {
    AstVisPrint::print(node) ;
    print(node) ;
}

void AstVisExplore::visit_node(AstNodeInt* integer) {}

void AstVisExplore::visit_node(AstNodeNeg* neg) {
    AstVisPrint::print(neg) ;
    getAstVis()->getOs() << ": "  << *Env->getVarType("~-") << std::endl ;
}

void AstVisExplore::visit_node(AstNodeVar* var) {
    //getAstVis()->getOs() << " : On cherche la variable " + var->getVar_name() + " dans l'environnement :\n"  ;
    EnvironmentMap::iterator itC = Env->getCurrent().find(var->getVar_name()) ;
    EnvironmentMap::iterator itG = Env->getGlobal().find(var->getVar_name()) ;
    if (itC != Env->getCurrent().end()) {
        //getAstVis()->getOs() << string("la variable " + var->getVar_name() + " est présente dans l'environnement courant\n")  ;
    }

    else if (itG != Env->getGlobal().end()) {
        //getAstVis()->getOs() << string("la variable " + var->getVar_name() + " est présente dans l'environnement global\n")  ;
    }
    else throw false ;
    
}

void AstVisExplore::visit_node(AstNodeLet* let) {}

void AstVisExplore::visit_node(AstNodeApp* app) {
    AstVisPrint::print(app) ;
    getAstVis()->getOs() << ": " << *Env->getVarType(app->getVar()->getVar_name()) << std::endl ;
}

void AstVisExplore::visit_node(AstNodeAdd* add) {
    AstVisPrint::print(add) ;
    getAstVis()->getOs() << ": "  << *Env->getVarType("+") << std::endl ;
}


AstVisExplore::~AstVisExplore() {
}

void AstVisRangeLet::visit_node(AstNode* node) {}
void AstVisRangeLet::visit_node(AstNodeInt* integer) {}
void AstVisRangeLet::visit_node(AstNodeNeg* neg) {}
void AstVisRangeLet::visit_node(AstNodeVar* var) {}
void AstVisRangeLet::visit_node(AstNodeApp* app) {}
void AstVisRangeLet::visit_node(AstNodeAdd* add) {}

void AstVisRangeLet::visit_node(AstNodeLet* let) {
    AstVisPrint::print(let) ;
    AstVisInfer * infer = (AstVisInfer*) getAstVis()->GetPostfix() ;
    getAstVis()->getOs() << " : " << *infer->getType() << " " ;
    Env->addVar(let->getVar().getVar_name(), infer->getType()) ;
    Env->printCurrent() ;
    getAstVis()->getOs() << std::endl ;
    infer->setType(NULL) ;
}

AstVisRangeLet::~AstVisRangeLet() {}

AstVisInfer::AstVisInfer(Environment * Env) :
AstVisPrint(), Env(Env), node(NULL), type(NULL) {
}

AstNode* AstVisInfer::getNode() const {
    return node ;
}

void AstVisInfer::setNode(AstNode* node) {
    this->node = node;
}

Type* AstVisInfer::getType() const {
    return type;
}

void AstVisInfer::setType(Type* type) {
    this->type = type;
}

AstVisInfer::~AstVisInfer() { Type::deleteTypeRec(type) ; }

void AstVisInfer::print(Type *type, AstNode* node) {
    getAstVis()->getOs() << " : " << *type << std::endl ; 
}

void AstVisInfer::visit_node(AstNode* node) {
    AstVisPrint::print(node) ; 
}

void AstVisInfer::visit_node(AstNodeInt* integer) {
    AstVisPrint::print(integer) ;
    Type * typeInt = TypeSimpleFactory(INT).create() ;
    print(typeInt, integer) ;
    node = integer ;
    typeInt->setNext(type) ;
    type = typeInt ;
}

void AstVisInfer::visit_node(AstNodeNeg* neg) {
    UnificationNode(neg, Type::copyTypeRec(Env->getVarType("~-"))) ;
}

void AstVisInfer::visit_node(AstNodeVar* var) {
    AstVisPrint::print(var) ;
    Type *VarType = Type::copyTypeRec(Env->getVarType(var->getVar_name())) ;
    getAstVis()->getOs() << " : " << *VarType << std::endl ;
    node = var ;
    VarType->setNext(type) ;
    type = VarType ;
}

void AstVisInfer::visit_node(AstNodeLet* let) {
    AstVisPrint::print(let) ;
    getAstVis()->getOs() << ": On retire la variable de l'environnement courant " << std::endl ;
    Env->removeVar(let->getVar().getVar_name()) ;
}

void AstVisInfer::visit_node(AstNodeApp* app) {
    UnificationNode(app, Type::copyTypeRec(Env->getVarType(app->getVar()->getVar_name()))) ;
}

void AstVisInfer::visit_node(AstNodeAdd* add) {
    UnificationNode(add, Type::copyTypeRec(Env->getVarType("+"))) ;
}

bool AstVisInfer::isWholeProgramCorrectlyTyped() {
    return type->GetType() == Simple && type->GetTypeSimple()->getType() == UNIT ;
}

void AstVisInfer::UnificationNode (AstNode *node, Type *typeNode) {
    AstVisPrint::print(node) ;
    try {
        type = Type::Unification(typeNode, type) ;
    } catch (bool res) {
        Type::deleteTypeRec(typeNode) ;
        throw res ;
    }
    getAstVis()->getOs() << ": " << *type << std::endl ;
}