#include <iostream>
#include "AstNodeNot.hpp"


AstNodeNot::AstNodeNot(AstNode *t1){
    this->class_code = C_NOT;
    this->t1 = t1;
}

AstNodeNot::~AstNodeNot(){
    this->class_code = C_NOT;
}

bool AstNodeNot::infer_types(){
    return true;
}

void AstNodeNot::print(){
}
