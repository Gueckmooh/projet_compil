#include "AstNode.hpp"
#include "AstNodeUnary.hpp"
#include "AstVisitor.hpp"
#include "utils.h"
#include "AstNodeLeaf.hpp"

AstNodeUnary::AstNodeUnary(AstNode * t1) :
AstNode(class_code), t1(t1) {}

void AstNodeUnary::traversal(AstVisitor & vis) {
    t1->apply(vis) ;
}

AstNodeUnary::~AstNodeUnary() {}

AstNodeApp::AstNodeApp(std::list<AstNode *> args_list, AstNode * t1) :
AstNode(C_APP), AstNodeTuple(args_list), AstNodeUnary(t1) {}
std::ostream& AstNodeApp::print(std::ostream& os) { return AstNode::print(os) ; }
void AstNodeApp::traversal(AstVisitor & vis) {
    AstNodeUnary::traversal(vis) ;
    AstNodeTuple::traversal(vis) ;
}
AstNodeApp::~AstNodeApp() {}

AstNodeFneg::AstNodeFneg(AstNode * t1) :
AstNode(C_FNEG), AstNodeUnary(t1) {}
AstNodeFneg::~AstNodeFneg() {}

AstNodeNeg::AstNodeNeg(AstNode * t1) :
AstNode(C_NEG), AstNodeUnary(t1) {}
AstNodeNeg::~AstNodeNeg() {}

AstNodeNot::AstNodeNot(AstNode * t1) :
AstNode(C_NOT), AstNodeUnary(t1) {}
AstNodeNot::~AstNodeNot() {}

FunDef::FunDef(std::string var_name, TCode tc, std::list<std::string> args_list, AstNode * body) :
AstNode(C_FUNDEF, TY_FUN, var_name), AstNodeVar(var_name), AstNodeUnary(body), args_list(args_list) {}
std::ostream& FunDef::print(std::ostream& os) {
    AstNodeVar::print(os) ;
    os << std::string(" ") ;
    print_str_list(os, args_list);
    return os ;
}
FunDef::~FunDef() {}
void FunDef::traversal(AstVisitor & vis) {
    AstNodeUnary::traversal(vis) ;
}

AstNodeLetRec::AstNodeLetRec(FunDef* fun_def, AstNode * t1) :
AstNode(C_LETREC), AstNodeUnary(t1), fun_def(fun_def) {}
void AstNodeLetRec::traversal(AstVisitor& vis) {
    fun_def->apply(vis) ;
    t1->apply(vis) ;
}
AstNodeLetRec::~AstNodeLetRec() {}
