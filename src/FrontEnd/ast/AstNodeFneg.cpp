#include <iostream>
#include "AstNodeFneg.hpp"


AstNodeFneg::AstNodeFneg(AstNode *t1){
    this->t1 = t1;
}

AstNodeFneg::~AstNodeFneg(){}

bool AstNodeFneg::infer_types(){
    return true;
}

void AstNodeFneg::print(){
}
