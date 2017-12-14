#include <iostream>
#include "AstNodeAdd.hpp"
#include "AstVisitor.hpp"

AstNodeAdd::AstNodeAdd(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeAdd::~AstNodeAdd(){}

bool AstNodeAdd::infer_types(){
    return true;
}

void AstNodeAdd::print(){
}

void AstNodeAdd::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
}
