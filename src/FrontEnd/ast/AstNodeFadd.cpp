#include <iostream>
#include "AstNodeFadd.hpp"
#include "AstVisitor.hpp"


AstNodeFadd::AstNodeFadd(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFadd::~AstNodeFadd(){}

bool AstNodeFadd::infer_types(){
    return true;
}

void AstNodeFadd::print(){
}

void AstNodeFadd::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
}
