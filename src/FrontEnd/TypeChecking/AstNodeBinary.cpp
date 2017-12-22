#include "AstNode.hpp"
#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "utils.h"
#include "AstNodeUnary.hpp"

AstNodeBinary::AstNodeBinary(AstNode * t1, AstNode * t2) :
AstNode(class_code), t1(t1), t2(t2) {
}

AstNode* AstNodeBinary::getT1() const {
    return t1;
}

AstNode* AstNodeBinary::getT2() const {
    return t2;
}


void AstNodeBinary::traversal(AstVisitor* vis) {
    t1->apply(vis) ;
    t2->apply(vis) ;
}

AstNodeBinary::~AstNodeBinary() {}

AstNodeAdd::AstNodeAdd(AstNode * t1, AstNode * t2) :
AstNode(C_ADD), AstNodeBinary(t1, t2) {
}

void AstNodeAdd::accept(AstVisAbstract * vis) {
    vis->visit_node(this) ;
}

AstNodeAdd::~AstNodeAdd(){}

AstNodeArray::AstNodeArray(AstNode * t1, AstNode * t2) :
AstNode(C_ARRAY), AstNodeBinary(t1, t2) {
}

void AstNodeArray::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeArray::~AstNodeArray() {}

AstNodeEq::AstNodeEq(AstNode * t1, AstNode * t2) :
AstNode(C_EQ), AstNodeBinary(t1, t2) {
}

void AstNodeEq::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeEq::~AstNodeEq() {}

AstNodeFadd::AstNodeFadd(AstNode * t1, AstNode * t2) :
AstNode(C_FADD), AstNodeBinary(t1, t2) {
}

void AstNodeFadd::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeFadd::~AstNodeFadd() {}

AstNodeFdiv::AstNodeFdiv(AstNode * t1, AstNode * t2) :
AstNode(C_FDIV), AstNodeBinary(t1, t2) {
}

void AstNodeFdiv::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeFdiv::~AstNodeFdiv() {}

AstNodeFmul::AstNodeFmul(AstNode * t1, AstNode * t2) :
AstNode(C_FMUL), AstNodeBinary(t1, t2) {
}

void AstNodeFmul::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeFmul::~AstNodeFmul() {}

AstNodeFsub::AstNodeFsub(AstNode * t1, AstNode * t2) :
AstNode(C_FSUB), AstNodeBinary(t1, t2) {
}

void AstNodeFsub::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeFsub::~AstNodeFsub() {}

AstNodeGet::AstNodeGet(AstNode * t1, AstNode * t2) :
AstNode(C_GET), AstNodeBinary(t1, t2) {
}

void AstNodeGet::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeGet::~AstNodeGet() {}

AstNodeLe::AstNodeLe(AstNode * t1, AstNode * t2) :
AstNode(C_LE), AstNodeBinary(t1, t2) {
}

void AstNodeLe::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeLe::~AstNodeLe() {}

AstNodeLet::AstNodeLet(AstNode * t1, AstNode * t2, std::string var_name) :
AstNode(C_LET), AstNodeVar(var_name), AstNodeBinary(t1, t2), value(std::string()) {
}

std::string AstNodeLet::getValue() const {
    return value;
}

void AstNodeLet::setValue(std::string value) {
    this->value = value;
}

void AstNodeLet::traversal(AstVisitor* vis) { AstNodeBinary::traversal(vis) ; }

std::ostream& AstNodeLet::print(std::ostream& os) {
    return AstNodeVar::print(os) ;
}

void AstNodeLet::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeLet::~AstNodeLet() {}

AstNodeLetTuple::AstNodeLetTuple(std::list<std::string> var_list, AstNode * t1, AstNode * t2) :
AstNode(C_LETTUPLE), AstNodeBinary(t1, t2), var_list(var_list) {}
void AstNodeLetTuple::traversal(AstVisitor* vis) {
    AstNodeBinary::traversal(vis) ;
}

std::ostream& AstNodeLetTuple::print(std::ostream& os) {
    print_str_list(os, var_list) ;
    return os ;
}

void AstNodeLetTuple::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeLetTuple::~AstNodeLetTuple() {}

AstNodeSub::AstNodeSub(AstNode * t1, AstNode * t2) :
AstNode(C_SUB), AstNodeBinary(t1, t2) {
}

void AstNodeSub::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeSub::~AstNodeSub() {
}
