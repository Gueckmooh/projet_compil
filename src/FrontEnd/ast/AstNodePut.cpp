#include <iostream>
#include <string>
#include "AstNodePut.hpp"


AstNodePut::AstNodePut(AstNode *t1, AstNode *t2, AstNode *t3){
    this->t1 = t1;
    this->t2 = t2;
    this->t3 = t3;
}

AstNodePut::~AstNodePut(){}

bool AstNodePut::infer_types(){
    return true;
}

void AstNodePut::print(){
}
