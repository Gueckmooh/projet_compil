#include <iostream>
#include "AstNodeEq.hpp"
#include "AstVisitor.hpp"


AstNodeEq::AstNodeEq(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeEq::~AstNodeEq(){}

bool AstNodeEq::infer_types(){
    return true;
}

void AstNodeEq::print(){
}

void AstNodeEq::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
}
