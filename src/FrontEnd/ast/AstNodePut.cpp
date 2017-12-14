#include <iostream>
#include <string>
#include "AstNodePut.hpp"


AstNodePut::AstNodePut(AstNode *t1, AstNode *t2, AstNode *t3){
    this->class_code = C_PUT;
    this->t1 = t1;
    this->t2 = t2;
    this->t3 = t3;
}

AstNodePut::~AstNodePut(){
    this->class_code = C_PUT;
}

bool AstNodePut::infer_types(){
    return true;
}

void AstNodePut::print(){
}
