#include <iostream>
#include "AstNodeFloat.hpp"
#include "AstVisitor.hpp"


AstNodeFloat::AstNodeFloat(float b){
    this->f = f;
}

AstNodeFloat::~AstNodeFloat(){}

bool AstNodeFloat::infer_types(){
    return true;
}

void AstNodeFloat::print(){
}

void AstNodeFloat::traversal(AstVisitor *vis){
    vis->visit_node(this);
}
