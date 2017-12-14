#include <iostream>
#include "AstNodeAdd.hpp"


AstNodeAdd::AstNodeAdd(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeAdd::~AstNodeAdd(){}

bool AstNodeAdd::infer_types(){
    return true;
}

void AstNodeAdd::print(){
}
