#include <iostream>
#include "AstNodeNeg.hpp"


AstNodeNeg::AstNodeNeg(AstNode *t1){
    this->t1 = t1;
}

AstNodeNeg::~AstNodeNeg(){}

bool AstNodeNeg::infer_types(){
    return true;
}

void AstNodeNeg::print(){
}

void AstNodeNeg::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
}
