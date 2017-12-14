#include <iostream>
#include "AstNodeSub.hpp"


AstNodeSub::AstNodeSub(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeSub::~AstNodeSub(){}

bool AstNodeSub::infer_types(){
    return true;
}

void AstNodeSub::print(){
}

void AstNodeSub::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
}
