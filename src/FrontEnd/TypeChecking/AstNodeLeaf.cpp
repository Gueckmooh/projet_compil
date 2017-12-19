#include "AstNode.hpp"
#include "AstNodeLeaf.hpp"
#include "utils.h"
#include "assert.h"
#include "AstVisitor.hpp"

AstNodeLeaf::AstNodeLeaf() :
AstNode(class_code) {}
void AstNodeLeaf::traversal(AstVisitor & vis) {}
AstNodeLeaf::~AstNodeLeaf() {}

AstNodeBool::AstNodeBool(bool b) :
AstNode(C_BOOL, TY_BOOL), AstNodeLeaf(), b(b) {}
std::ostream& AstNodeBool::print(std::ostream& os) { return os << std::string(" " + b) ; }
AstNodeBool::~AstNodeBool(){}

AstNodeFloat::AstNodeFloat(float f) :
AstNode(C_FLOAT, TY_FLOAT), AstNodeLeaf(), f(f) {}
std::ostream& AstNodeFloat::print(std::ostream& os) { return os << std::string(" " + std::to_string(f)) ; }
AstNodeFloat::~AstNodeFloat() {}

AstNodeInt::AstNodeInt(int i) :
AstNode(C_INT, TY_INT), AstNodeLeaf(), i(i) {}
std::ostream& AstNodeInt::print(std::ostream& os) { return os << std::string(" " + std::to_string(i)) ; }
AstNodeInt::~AstNodeInt() {}

AstNodeTuple::AstNodeTuple(std::list<AstNode *> var_list) : 
AstNode(C_TUPLE, TY_TUPLE), AstNodeLeaf(), var_list(var_list) {}
std::ostream& AstNodeTuple::print(std::ostream& os) { return AstNode::print(os) ; }
void AstNodeTuple::traversal(AstVisitor& vis) {
for (std::list<AstNode *>::iterator it = var_list.begin() ; it != var_list.end() ; it++)
        (*it)->apply(vis) ;   
}
AstNodeTuple::~AstNodeTuple() {}

AstNodeUnit::AstNodeUnit() :
AstNode(C_UNIT, TY_UNIT), AstNodeLeaf() {}
AstNodeUnit::~AstNodeUnit() {}

AstNodeVar::AstNodeVar(std::string var_name) :
AstNode(C_VAR, TY_VAR, var_name), AstNodeLeaf(), var_name(var_name) {}
std::ostream& AstNodeVar::print(std::ostream& os) { return os << std::string(" " + var_name) ; }
AstNodeVar::~AstNodeVar() {
}
