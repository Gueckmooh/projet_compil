#include <iostream>
#include "AstNodeNeg.hpp"


AstNodeNeg::AstNodeNeg(AstNode *t1){
    this->t1 = t1;
}

AstNodeNeg::~AstNodeNeg(){}

bool AstNodeNeg::infer_types(){
    return true;
}

void AstNodeNeg::print(){
}
