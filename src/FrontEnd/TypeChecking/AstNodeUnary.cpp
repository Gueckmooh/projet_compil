#include "AstNode.hpp"
#include "AstNodeLeaf.hpp"
#include "AstNodeUnary.hpp"
#include "AstVisitor.hpp"
#include "utils.h"
#include "TypeFactory.hpp"

AstNodeUnary::AstNodeUnary(int class_code, AstNode * t1) :
AstNode(class_code), t1(t1) {}

AstNode* AstNodeUnary::getT1() const {
    return t1;
}

void AstNodeUnary::traversal(AstVisitor *vis) {
    t1->apply(vis) ;
}

AstNodeUnary::~AstNodeUnary() {}

AstNodeApp::AstNodeApp(std::vector<AstNode *> args_list, AstNodeVar *var) :
AstNodeTuple(args_list), var(var) { class_code = C_APP ; }

AstNodeVar* AstNodeApp::getVar() const {
    return var;
}

std::ostream& AstNodeApp::print(std::ostream& os) {
    os << *var << " " ;
    AstNodeTuple::print(os) ;
    return os ;
}

void AstNodeApp::traversal(AstVisitor * vis) {
    AstNodeTuple::traversal(vis) ;
}

void AstNodeApp::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeApp::~AstNodeApp() { delete var ; }

AstNodeFneg::AstNodeFneg(AstNode * t1) :
AstNodeUnary(C_FNEG, t1) {}

void AstNodeFneg::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeFneg::~AstNodeFneg() {}

AstNodeNeg::AstNodeNeg(AstNode * t1) :
AstNodeUnary(C_NEG, t1) {}

void AstNodeNeg::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeNeg::~AstNodeNeg() {}

AstNodeNot::AstNodeNot(AstNode * t1) :
AstNodeUnary(C_NOT, t1) {}

void AstNodeNot::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeNot::~AstNodeNot() {}

// FunDef

FunDef::FunDef(std::string var_name, std::vector<std::string> args_list, AstNode * body) :
AstNodeUnary(C_FUNDEF, body), var(AstNodeVar(var_name)), args_list(args_list) {}

std::ostream& FunDef::print(std::ostream& os) {
    os << var << " " ;
    print_str_list(os, args_list);
    return os ;
}

void FunDef::traversal(AstVisitor * vis) {
    AstNodeUnary::traversal(vis) ;
}

void FunDef::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

FunDef::~FunDef() {}

// Let Rec

AstNodeLetRec::AstNodeLetRec(FunDef* fun_def, AstNode * t1) :
AstNodeUnary(C_LETREC, t1), fun_def(fun_def) {}

void AstNodeLetRec::traversal(AstVisitor* vis) {
    fun_def->apply(vis) ;
    t1->apply(vis) ;

}

void AstNodeLetRec::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}


AstNodeLetRec::~AstNodeLetRec() {}
