#include <iostream>
#include "AstNodeSub.hpp"


AstNodeSub::AstNodeSub(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeSub::~AstNodeSub(){}

bool AstNodeSub::infer_types(){
    return true;
}

void AstNodeSub::print(){
}
