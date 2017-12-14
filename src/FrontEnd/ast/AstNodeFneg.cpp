#include <iostream>
#include "AstNodeFneg.hpp"
#include "AstVisitor.hpp"


AstNodeFneg::AstNodeFneg(AstNode *t1){
    this->t1 = t1;
}

AstNodeFneg::~AstNodeFneg(){}

bool AstNodeFneg::infer_types(){
    return true;
}

void AstNodeFneg::print(){
}

void AstNodeFneg::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
}
