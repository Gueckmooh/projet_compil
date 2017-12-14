#include <iostream>
#include "AstNodeLe.hpp"


AstNodeLe::AstNodeLe(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeLe::~AstNodeLe(){}

bool AstNodeLe::infer_types(){
    return true;
}

void AstNodeLe::print(){
}
