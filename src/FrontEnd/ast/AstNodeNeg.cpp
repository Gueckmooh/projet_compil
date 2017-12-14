#include <iostream>
#include "AstNodeNeg.hpp"


AstNodeNeg::AstNodeNeg(AstNode *t1){
    this->class_code = C_NEG;
    this->t1 = t1;
}

AstNodeNeg::~AstNodeNeg(){
    this->class_code = C_NEG;
}

bool AstNodeNeg::infer_types(){
    return true;
}

void AstNodeNeg::print(){
}
