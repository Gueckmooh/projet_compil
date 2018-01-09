#include "AstNode.hpp"
#include "AstNodeTernary.hpp"
#include "AstVisitor.hpp"

AstNodeTernary::AstNodeTernary(int class_code, AstNode* t1, AstNode* t2, AstNode* t3) :
AstNode(class_code), t1(t1), t2(t2), t3(t3) {}

void AstNodeTernary::traversal(AstVisitor* vis) {
    t1->apply(vis) ;
    t2->apply(vis) ;
    t3->apply(vis) ;
}

AstNodeTernary::~AstNodeTernary() {}

AstNodeIf::AstNodeIf(AstNode* t1, AstNode* t2, AstNode* t3) :
AstNodeTernary(C_IF, t1, t2, t3) {}

void AstNodeIf::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodeIf::~AstNodeIf() {}

AstNodePut::AstNodePut(AstNode* t1, AstNode* t2, AstNode* t3) :
AstNodeTernary(C_PUT, t1, t2, t3) {}

void AstNodePut::accept(AstVisAbstract* vis) {
    vis->visit_node(this) ;
}

AstNodePut::~AstNodePut() {}
