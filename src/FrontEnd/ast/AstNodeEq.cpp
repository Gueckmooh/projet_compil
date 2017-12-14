#include <iostream>
#include "AstNodeEq.hpp"


AstNodeEq::AstNodeEq(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeEq::~AstNodeEq(){}

bool AstNodeEq::infer_types(){
    return true;
}

void AstNodeEq::print(){
}
