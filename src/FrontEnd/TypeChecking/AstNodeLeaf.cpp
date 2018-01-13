#include "AstNode.hpp"
#include "AstNodeLeaf.hpp"
#include <iomanip>

AstNodeLeaf::AstNodeLeaf(int class_code) :
AstNode(class_code) {}
void AstNodeLeaf::traversal(AstVisitor * vis) {}
AstNodeLeaf::~AstNodeLeaf() {}

AstNodeBool::AstNodeBool(bool b) :
AstNodeLeaf(C_BOOL), b(b) {}

std::ostream& AstNodeBool::print(std::ostream& os) {
    return os << std::boolalpha << b ;
}

void AstNodeBool::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeBool::~AstNodeBool(){}

AstNodeFloat::AstNodeFloat(float f) :
AstNodeLeaf(C_FLOAT), f(f) {}

std::ostream& AstNodeFloat::print(std::ostream& os) {
    return os << std::showpoint << std::setprecision(1) << f ;
}

void AstNodeFloat::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeFloat::~AstNodeFloat() {}

AstNodeInt::AstNodeInt(int i) :
AstNodeLeaf(C_INT), i(i) {}

std::ostream& AstNodeInt::print(std::ostream& os) {
    return os << std::string(std::to_string(i)) ;
}

void AstNodeInt::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeInt::~AstNodeInt() {}

AstNodeTuple::AstNodeTuple(std::vector<AstNode *> var_list) : 
AstNodeLeaf(C_TUPLE), var_list(var_list) {}

std::ostream& AstNodeTuple::print(std::ostream& os) {
    for (std::vector<AstNode *>::iterator it = var_list.begin() ; it != var_list.end() ; it++)
        os << **it  << " " ;
    return os ;
}

void AstNodeTuple::traversal(AstVisitor* vis) {
    std::vector<AstNode *>::iterator it = var_list.begin() ;
    (*it++)->apply(vis) ;
    for ( ; it != var_list.end() ; it++) {
        accept(vis->GetInfix()) ;
        (*it)->apply(vis) ;
    }
}

std::vector<AstNode*> AstNodeTuple::getVar_list() const {
    return var_list;
}


void AstNodeTuple::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}


AstNodeTuple::~AstNodeTuple() {}

AstNodeUnit::AstNodeUnit() :
AstNodeLeaf(C_UNIT) {
}

std::ostream& AstNodeUnit::print(std::ostream& os) {
    return os << "()" ;
}


void AstNodeUnit::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeUnit::~AstNodeUnit() {}

AstNodeVar::AstNodeVar(std::string var_name) :
AstNodeLeaf(C_VAR), var_name(var_name) {}

std::ostream& AstNodeVar::print(std::ostream& os) {
    return os << std::string(var_name) ;
}

void AstNodeVar::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

std::string & AstNodeVar::getVar_name() {
    return var_name;
}

AstNodeVar::~AstNodeVar() {}