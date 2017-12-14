#include <iostream>
#include "AstNodeFsub.hpp"
#include "AstVisitor.hpp"


AstNodeFsub::AstNodeFsub(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFsub::~AstNodeFsub(){}

bool AstNodeFsub::infer_types(){
    return true;
}

void AstNodeFsub::print(){
}

void AstNodeFsub::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
}
