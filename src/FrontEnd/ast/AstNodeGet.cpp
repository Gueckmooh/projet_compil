#include <iostream>
#include <string>
#include "AstNodeGet.hpp"
#include "AstVisitor.hpp"


AstNodeGet::AstNodeGet(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeGet::~AstNodeGet(){}

bool AstNodeGet::infer_types(){
    return true;
}

void AstNodeGet::print(){
}

void AstNodeGet::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
}
