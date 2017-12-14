#include <iostream>
#include "AstNodeFmul.hpp"
#include "AstVisitor.hpp"


AstNodeFmul::AstNodeFmul(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFmul::~AstNodeFmul(){}

bool AstNodeFmul::infer_types(){
    return true;
}

void AstNodeFmul::print(){
}

void AstNodeFmul::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
}
