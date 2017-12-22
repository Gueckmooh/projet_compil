#include "AstNode.hpp"
#include "AstNodeLeaf.hpp"
#include "utils.h"
#include "assert.h"
#include "AstVisitor.hpp"
#include "AstVis.hpp"

AstNodeLeaf::AstNodeLeaf() :
AstNode(class_code) {}
void AstNodeLeaf::traversal(AstVisitor * vis) {}
AstNodeLeaf::~AstNodeLeaf() {}

AstNodeBool::AstNodeBool(bool b) :
AstNode(C_BOOL, TY_BOOL), AstNodeLeaf(), b(b) {}

std::ostream& AstNodeBool::print(std::ostream& os) {
    return os << std::string("" + b) ;
}

void AstNodeBool::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeBool::~AstNodeBool(){}

AstNodeFloat::AstNodeFloat(float f) :
AstNode(C_FLOAT, TY_FLOAT), AstNodeLeaf(), f(f) {}

std::ostream& AstNodeFloat::print(std::ostream& os) {
    return os << std::string(std::to_string(f)) ;
}

void AstNodeFloat::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeFloat::~AstNodeFloat() {}

AstNodeInt::AstNodeInt(int i) :
AstNode(C_INT, TY_INT), AstNodeLeaf(), i(i) {}
std::ostream& AstNodeInt::print(std::ostream& os) {
    return os << std::string(std::to_string(i)) ;
}

void AstNodeInt::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeInt::~AstNodeInt() {}

AstNodeTuple::AstNodeTuple(std::list<AstNode *> var_list) : 
AstNode(C_TUPLE, TY_TUPLE), AstNodeLeaf(), var_list(var_list) {}

std::ostream& AstNodeTuple::print(std::ostream& os) {
    return AstNode::print(os) ;
}

void AstNodeTuple::traversal(AstVisitor* vis) {
    for (std::list<AstNode *>::iterator it = var_list.begin() ; it != var_list.end() ; it++)
        (*it)->apply(vis) ;   
}

std::list<AstNode*> AstNodeTuple::getVar_list() const {
    return var_list;
}


void AstNodeTuple::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}


AstNodeTuple::~AstNodeTuple() {}

AstNodeUnit::AstNodeUnit() :
AstNode(C_UNIT, TY_UNIT), AstNodeLeaf() {
}

void AstNodeUnit::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeUnit::~AstNodeUnit() {}

AstNodeVar::AstNodeVar(std::string var_name) :
AstNode(C_VAR, TY_UNDEFINED), AstNodeLeaf(), var_name(var_name) {}

std::list<TCode> AstNodeVar::getTcval() const {
    return tcval;
}

void AstNodeVar::setTcval(std::list<TCode> tcval) {
    this->tcval = tcval;
}

std::ostream& AstNodeVar::print(std::ostream& os) {
    return os << std::string(var_name) ;
}

void AstNodeVar::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

std::string  AstNodeVar::getVar_name() {
    return var_name;
}

AstNodeVar::~AstNodeVar() {
}

std::string AstNodeTuple::printType() {
    std::string ty = "" ;
    std::list<AstNode *>::iterator it = var_list.begin() ;
    ty += (*it++)->printType() ;
    for (  ; it != var_list.end() ; it++)
        ty += " * " + (*it)->printType() ;
    
    return ty ;
}

std::string AstNodeVar::printType() {
    std::string ty = var_name + " : " ;
    std::list<TCode>::iterator it = tcval.begin() ;
    ty += TCode_to_string((*it++)) ;
    for (  ; it != tcval.end() ; it++)
        ty += " -> " + TCode_to_string(*it) ;
    
    return ty ;
}