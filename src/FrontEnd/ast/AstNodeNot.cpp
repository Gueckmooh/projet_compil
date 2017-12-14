#include <iostream>
#include "AstNodeNot.hpp"


AstNodeNot::AstNodeNot(AstNode *t1){
    this->t1 = t1;
}

AstNodeNot::~AstNodeNot(){}

bool AstNodeNot::infer_types(){
    return true;
}

void AstNodeNot::print(){
}
