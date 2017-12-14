#include <iostream>
#include "AstNodeIf.hpp"
#include "AstVisitor.hpp"


AstNodeIf::AstNodeIf(AstNode *t1, AstNode *t2, AstNode *t3){
    this->t1 = t1;
    this->t2 = t2;
    this->t3 = t3;
}

AstNodeIf::~AstNodeIf(){}

bool AstNodeIf::infer_types(){
    return true;
}

void AstNodeIf::print(){
}

void AstNodeIf::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
    this->t3->traversal(vis);
}
