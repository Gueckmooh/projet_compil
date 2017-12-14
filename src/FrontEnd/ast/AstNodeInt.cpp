#include <iostream>
#include "AstNodeInt.hpp"
#include "AstVisitor.hpp"


AstNodeInt::AstNodeInt(int i){
    this->i = i;
}

AstNodeInt::~AstNodeInt(){}

bool AstNodeInt::infer_types(){
    return true;
}

void AstNodeInt::print(){
}

void AstNodeInt::traversal(AstVisitor *vis){
    vis->visit_node(this);
}
