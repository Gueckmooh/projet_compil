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
#include <list>

// Environment

Environment::Environment() : os(NULL), args(NULL) {
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

Type* Environment::getArgs() const {
    return args;
}

void Environment::setArgs(Type* args) {
    this->args = args;
}

Type* Environment::getVarType(string key) {
    EnvironmentMap::iterator it = CM.find(key) ;
    if (it != CM.end())
        return it->second ;
    it = GM.find(key) ;
    if (it != GM.end())
        return it->second ;
    std::cout << "UNBOUND VALUE " << key << std::endl ;
    throw false ;
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

// AstVisExplore

AstVisExplore::AstVisExplore(Environment * Env) : 
AstVisPrint(), Env(Env)  {
}

void AstVisExplore::print(AstNode* node) {
    getAstVis()->getOs() << " : Rien à ajouter dans l'environnement\n" ;
}

// Node

void AstVisExplore::visit_node(AstNode* node) {
    AstVisPrint::print(node) ;
    print(node) ;
}

// Leaves

inline void AstVisExplore::visit_node(AstNodeBool* boolean) {}
inline void AstVisExplore::visit_node(AstNodeFloat* floatingpoint) {}
inline void AstVisExplore::visit_node(AstNodeInt* integer) {}
inline void AstVisExplore::visit_node(AstNodeTuple* tuple) {}
inline void AstVisExplore::visit_node(AstNodeUnit* unit) {}

void AstVisExplore::visit_node(AstNodeVar* var) {
    EnvironmentMap::iterator itC = Env->getCurrent().find(var->getVar_name()) ;
    EnvironmentMap::iterator itG = Env->getGlobal().find(var->getVar_name()) ;
    if (itC != Env->getCurrent().end()) {
        //getAstVis()->getOs() << string("la variable " + var->getVar_name() + " est présente dans l'environnement courant\n")  ;
    }
    else if (itG != Env->getGlobal().end()) {
        //getAstVis()->getOs() << string("la variable " + var->getVar_name() + " est présente dans l'environnement global\n")  ;
    }
    else {
        getAstVis()->getOs() << "UNBOUND VALUE " << var->getVar_name() << std::endl ;
        throw false ;
    }
}

// Unary Nodes

void AstVisExplore::visit_node(AstNodeApp* app) {
    AstVisPrint::print(app) ;
    getAstVis()->getOs() << ": " << *Env->getVarType(app->getVar()->getVar_name()) << std::endl ;
}
void AstVisExplore::visit_node(FunDef* fundef) {
    AstVisPrint::print(fundef) ;
    Type * type = Env->getVarType(fundef->getVar().getVar_name()) ;
    for (auto arg : fundef->getArgs()) {
        Env->addVar(arg, new Type(TypeSimple::copyTypeSimple(type->GetTypeSimple()))) ;
        type = type->getNext() ;
    }
    Env->printCurrent() ;
    getAstVis()->getOs() << std::endl ;
}
void AstVisExplore::visit_node(AstNodeLetRec* letrec) {
    AstVisPrint::print(letrec) ;
    getAstVis()->getOs() << letrec->getFunDef()->getVar() ;
    for (auto arg : letrec->getFunDef()->getArgs())
        getAstVis()->getOs() << " " << arg ;
    Env->addVar(letrec->getFunDef()->getVar().getVar_name(), TypeFactory::createPoly(letrec->getFunDef()->getArgs().size() + 1)) ;
    getAstVis()->getOs() << " : " << *Env->getVarType(letrec->getFunDef()->getVar().getVar_name()) << " " ;
    Env->printCurrent() ;
    getAstVis()->getOs() << std::endl ;
    TypeSimple::resetNextPoly() ;
}
void AstVisExplore::visit_node(AstNodeNeg* neg) {
    AstVisPrint::print(neg) ;
    getAstVis()->getOs() << ": "  << *Env->getVarType("~-") << std::endl ;
}

// Binary Nodes

void AstVisExplore::visit_node(AstNodeAdd* add) {
    AstVisPrint::print(add) ;
    getAstVis()->getOs() << ": "  << *Env->getVarType("+") << std::endl ;
}
inline void AstVisExplore::visit_node(AstNodeLet* let) {}
inline void AstVisExplore::visit_node(AstNodeLetTuple* lettuple) {}
void AstVisExplore::visit_node(AstNodeSub* sub) {
    AstVisPrint::print(sub) ;
    getAstVis()->getOs() << ": "  << *Env->getVarType("-") << std::endl ;
}

AstVisExplore::~AstVisExplore() {
}

// AstVisRangeLet

void AstVisRangeLet::addType(Type* type) {
    switch (type->GetType()) {
        case Simple :
            types.push_back(InitTypeComposed(Simple,type->GetTypeSimple()->getType())) ;
            Type::deleteType(type) ;
            break ;
        case Polymorphe :
            types.push_back(InitTypeComposed(Polymorphe, type->GetTypeSimple()->getType(), type->GetTypeSimple()->getPoly())) ;
            Type::deleteType(type) ;
            break ;
        case Tuple :
            types.push_back(InitTypeComposed(Tuple, type->GetTypeComposed())) ;
            break ;
        case Application :
            types.push_back(InitTypeComposed(Application, type->GetTypeComposed())) ;
            break ;
        default :
            assert(false) ;
    }
}

void AstVisRangeLet::UnificationTuple (VarIt *it, VarIt end, TypeComposed **typeMember) {
    if(*typeMember) {
        switch ((*typeMember)->getType()) {
            case Simple : case Polymorphe :
                Env->addVar(**it, new Type((*typeMember)->getSimple())) ;
                break ;
            case Tuple :
                Env->addVar(**it, new Type((*typeMember)->getTuple())) ;
                break ;
            case Application :
                Env->addVar(**it, new Type((*typeMember)->getApp())) ;
                break ;
        }
        (*it)++ ;
        TypeComposed * next = (*typeMember)->getNext() ;
        UnificationTuple(it, end, &next) ;
        delete *typeMember ;
        *typeMember = NULL ;
    }
}

// Node

inline void AstVisRangeLet::visit_node(AstNode* node) {}

// Leaves

inline void AstVisRangeLet::visit_node(AstNodeBool* boolean) {}
inline void AstVisRangeLet::visit_node(AstNodeFloat* floatingpoint) {}
inline void AstVisRangeLet::visit_node(AstNodeInt* integer) {}
void AstVisRangeLet::visit_node(AstNodeTuple* tuple) {
    AstVisInfer * infer = (AstVisInfer *) getAstVis()->GetPostfix() ;
    addType(infer->getType()) ;
    infer->setType(NULL) ;
}
inline void AstVisRangeLet::visit_node(AstNodeUnit* unit) {}
inline void AstVisRangeLet::visit_node(AstNodeVar* var) {}

// Unary Nodes

inline void AstVisRangeLet::visit_node(AstNodeApp* app) {}
inline void AstVisRangeLet::visit_node(FunDef* fundef) {}
void AstVisRangeLet::visit_node(AstNodeLetRec* letrec) {
    AstVisInfer * infer = (AstVisInfer *) getAstVis()->GetPostfix() ;
    Type::deleteTypeRec(infer->getType()) ;
    infer->setType(NULL) ;
}
inline void AstVisRangeLet::visit_node(AstNodeNeg* neg) {}

// Binary Nodes

inline void AstVisRangeLet::visit_node(AstNodeAdd* add) {}
void AstVisRangeLet::visit_node(AstNodeLet* let) {
    AstVisPrint::print(let) ;
    AstVisInfer * infer = (AstVisInfer*) getAstVis()->GetPostfix() ;
    getAstVis()->getOs() << " : " << *infer->getType() << " " ;
    Env->addVar(let->getVar().getVar_name(), infer->getType()) ;
    Env->printCurrent() ;
    getAstVis()->getOs() << std::endl ;
    infer->setType(NULL) ;
}

void AstVisRangeLet::visit_node(AstNodeLetTuple* lettuple) {
    AstVisPrint::print(lettuple) ;
    AstVisInfer * infer = (AstVisInfer*) getAstVis()->GetPostfix() ;
    VarIt it = lettuple->getVar_list().begin() ;
    if (infer->getType()->GetType() != Tuple || lettuple->getVar_list().size() != infer->getType()->GetTypeComposed()->size()) {
        getAstVis()->getOs() << "UNIFICATION TUPLE MEMBERS FAILURE" << std::endl ;
        throw false ;
    }
    getAstVis()->getOs() << ": " << *infer->getType() << " " ;
    TypeComposed * type = infer->getType()->GetTypeComposed() ;
    UnificationTuple(&it, lettuple->getVar_list().end(), &type) ;
    Env->printCurrent() ;
    getAstVis()->getOs() << std::endl ;
    delete infer->getType() ;
    infer->setType(NULL) ;
}
inline void AstVisRangeLet::visit_node(AstNodeSub* sub) {}

AstVisRangeLet::~AstVisRangeLet() {}

// AstVisInfer

AstVisInfer::AstVisInfer(Environment * Env) :
AstVisPrint(), Env(Env), node(NULL), type(NULL) {}

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

// Node

void AstVisInfer::visit_node(AstNode* node) {
    AstVisPrint::print(node) ; 
}

// Leaves

void AstVisInfer::InferLeaf(AstNodeLeaf* leaf, Type* type) {
    AstVisPrint::print(leaf) ;
    print(type, leaf) ;
    node = leaf ;
    type->setNext(this->type) ;
    this->type = type ;
}

void AstVisInfer::visit_node(AstNodeBool* boolean) {
    InferLeaf(boolean, Type::copyTypeRec(Env->getVarType("bool"))) ;
}

void AstVisInfer::visit_node(AstNodeFloat* floatingpoint) {
    InferLeaf(floatingpoint, Type::copyTypeRec(Env->getVarType("float"))) ;
}

void AstVisInfer::visit_node(AstNodeInt* integer) {
    InferLeaf(integer, Type::copyTypeRec(Env->getVarType("int"))) ;
}

void AstVisInfer::visit_node(AstNodeUnit* unit) {
    InferLeaf(unit, Type::copyTypeRec(Env->getVarType("unit"))) ;
}

void AstVisInfer::visit_node(AstNodeTuple* tuple) {
    AstVisRangeLet *VisTuple = (AstVisRangeLet*)getAstVis()->GetInfix() ;
    VisTuple->addType(type) ;
    type = new Type(TypeTupleFactory(VisTuple->types).create()) ;
    VisTuple->types.clear() ;
    AstVisPrint::print(tuple) ;
    print(type, tuple) ;
    node = tuple ;
}

void AstVisInfer::visit_node(AstNodeVar* var) {
    Type * varType ;
    InferLeaf(var, varType = Type::copyTypeRec(Env->getVarType(var->getVar_name()))) ;
}

// Unary Nodes

void AstVisInfer::visit_node(AstNodeApp* app) {
    UnificationNode(app, Type::copyTypeRec(Env->getVarType(app->getVar()->getVar_name()))) ;
    TypeSimple::printPoly() ;
    getAstVis()->getOs() << std::endl ;
    TypeSimple::resetPoly() ;
}

static Type * UpdateFunDef(Type *fun, Type *type) {
    if (!fun->getNext()) {
        Type::deleteType(fun) ;
        return type ;
    }
    Type * next = UpdateFunDef(fun->getNext(), type) ;
    Type * new_type = NULL ;
    if ((new_type = TypeSimple::getMappedPoly(fun->GetTypeSimple()->getPoly()))) {
        Type::deleteType(fun) ;
        fun = Type::copyType(new_type) ;
    }
    fun->setNext(next) ;
    return fun ;
}

void AstVisInfer::visit_node(FunDef* fundef) {
    AstVisPrint::print(fundef) ;
    Type * fun  = Env->getVarType(fundef->getVar().getVar_name()) ;
    Env->addVar(fundef->getVar().getVar_name(), fun = UpdateFunDef(fun, type)) ;
    for (auto arg : fundef->getArgs()) {
        Env->removeVar(arg) ;
    }
    getAstVis()->getOs() << " : " << *fun << " " ;
    Env->printCurrent() ;
    getAstVis()->getOs() << std::endl ;
    type = NULL ;
}
void AstVisInfer::visit_node(AstNodeLetRec* letrec) {
    AstVisPrint::print(letrec) ;
    getAstVis()->getOs() << letrec->getFunDef()->getVar() << " : On retire l'identificateur de la fonction de l'environnement courant" << std::endl ;
    Env->removeVar(letrec->getFunDef()->getVar().getVar_name()) ;
}
void AstVisInfer::visit_node(AstNodeNeg* neg) {
    UnificationNode(neg, Type::copyTypeRec(Env->getVarType("~-"))) ;
}

// Binary Nodes

void AstVisInfer::visit_node(AstNodeAdd* add) {
    UnificationNode(add, Type::copyTypeRec(Env->getVarType("+"))) ;
}

void AstVisInfer::visit_node(AstNodeLet* let) {
    AstVisPrint::print(let) ;
    getAstVis()->getOs() << " : On retire l'identificateur de la valeur de l'environnement courant" << std::endl ;
    Env->removeVar(let->getVar().getVar_name()) ;
}

void AstVisInfer::visit_node(AstNodeLetTuple* lettuple) {
    AstVisPrint::print(lettuple) ;
    getAstVis()->getOs() << " : On retire les identificateurs du tuple de l'environnement courant" << std::endl ;
    for (auto var : lettuple->getVar_list())
        Env->removeVar(var) ;
}

void AstVisInfer::visit_node(AstNodeSub* sub) {
    UnificationNode(sub, Type::copyTypeRec(Env->getVarType("-"))) ;
}

bool AstVisInfer::isWholeProgramCorrectlyTyped() {
    return type->GetType() == Simple && type->GetTypeSimple()->getType() == UNIT ;
}

void AstVisInfer::UnificationNode (AstNode *node, Type *typeNode) {
    AstVisPrint::print(node) ;
    try {
        type = Type::Unification(typeNode, type) ;
    } catch (bool exception) {
        getAstVis()->getOs() << "UNIFICATION FAILURE" << std::endl ;
        Type::deleteTypeRec(typeNode) ;
        throw exception ;
    }
    getAstVis()->getOs() << ": " << *type << std::endl ;
}