#include <iostream>
#include "AstNodeLe.hpp"
#include "AstVisitor.hpp"


AstNodeLe::AstNodeLe(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeLe::~AstNodeLe(){}

bool AstNodeLe::infer_types(){
    return true;
}

void AstNodeLe::print(){
}

void AstNodeLe::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
}
