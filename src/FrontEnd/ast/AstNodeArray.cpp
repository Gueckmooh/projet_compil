#include <iostream>
#include <string>
#include "AstNodeArray.hpp"


AstNodeArray::AstNodeArray(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeArray::~AstNodeArray(){}

bool AstNodeArray::infer_types(){
    return true;
}

void AstNodeArray::print(){
}
