#include "AstNode.hpp"
#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "utils.h"
#include "AstNodeUnary.hpp"

AstNodeBinary::AstNodeBinary(AstNode * t1, AstNode * t2) :
AstNode(class_code), t1(t1), t2(t2) {}

void AstNodeBinary::traversal(AstVisitor& vis) {
    t1->apply(vis) ;
    t2->apply(vis) ;
}

AstNodeBinary::~AstNodeBinary() {}

AstNodeAdd::AstNodeAdd(AstNode * t1, AstNode * t2) :
AstNode(C_ADD), AstNodeBinary(t1, t2) {}
AstNodeAdd::~AstNodeAdd(){}

AstNodeArray::AstNodeArray(AstNode * t1, AstNode * t2) :
AstNode(C_ARRAY), AstNodeBinary(t1, t2) {}
AstNodeArray::~AstNodeArray() {}

AstNodeEq::AstNodeEq(AstNode * t1, AstNode * t2) :
AstNode(C_EQ), AstNodeBinary(t1, t2) {}
AstNodeEq::~AstNodeEq() {}

AstNodeFadd::AstNodeFadd(AstNode * t1, AstNode * t2) :
AstNode(C_FADD), AstNodeBinary(t1, t2) {}
AstNodeFadd::~AstNodeFadd() {}

AstNodeFdiv::AstNodeFdiv(AstNode * t1, AstNode * t2) :
AstNode(C_FDIV), AstNodeBinary(t1, t2) {}
AstNodeFdiv::~AstNodeFdiv() {}

AstNodeFmul::AstNodeFmul(AstNode * t1, AstNode * t2) :
AstNode(C_FMUL), AstNodeBinary(t1, t2) {}
AstNodeFmul::~AstNodeFmul() {}

AstNodeFsub::AstNodeFsub(AstNode * t1, AstNode * t2) :
AstNode(C_FSUB), AstNodeBinary(t1, t2) {}
AstNodeFsub::~AstNodeFsub() {}

AstNodeGet::AstNodeGet(AstNode * t1, AstNode * t2) :
AstNode(C_GET), AstNodeBinary(t1, t2) {}
AstNodeGet::~AstNodeGet() {}

AstNodeLe::AstNodeLe(AstNode * t1, AstNode * t2) :
AstNode(C_LE), AstNodeBinary(t1, t2) {}
AstNodeLe::~AstNodeLe() {}

AstNodeLet::AstNodeLet(AstNode * t1, AstNode * t2, std::string var_name) :
AstNode(C_LET), AstNodeBinary(t1, t2) {}
void AstNodeLet::traversal(AstVisitor& vis) { AstNodeBinary::traversal(vis) ; }
std::ostream& AstNodeLet::print(std::ostream& os) { return os << std::string(" " + ty.getVar()) ; }
AstNodeLet::~AstNodeLet() {}

AstNodeLetTuple::AstNodeLetTuple(std::list<std::string> var_list, AstNode * t1, AstNode * t2) :
AstNode(C_LETTUPLE), AstNodeBinary(t1, t2), var_list(var_list) {}
void AstNodeLetTuple::traversal(AstVisitor& vis) { AstNodeBinary::traversal(vis) ; }
std::ostream& AstNodeLetTuple::print(std::ostream& os) {
    print_str_list(os, var_list) ;
    return os ;
}
AstNodeLetTuple::~AstNodeLetTuple() {}

AstNodeSub::AstNodeSub(AstNode * t1, AstNode * t2) :
AstNode(C_SUB), AstNodeBinary(t1, t2) {}
AstNodeSub::~AstNodeSub() {
}
