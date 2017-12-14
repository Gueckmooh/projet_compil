#include <iostream>
#include "AstNodeFdiv.hpp"


AstNodeFdiv::AstNodeFdiv(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFdiv::~AstNodeFdiv(){}

bool AstNodeFdiv::infer_types(){
    return true;
}

void AstNodeFdiv::print(){
}
