#include <iostream>
#include <string>
#include "AstNodeGet.hpp"


AstNodeGet::AstNodeGet(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeGet::~AstNodeGet(){}

bool AstNodeGet::infer_types(){
    return true;
}

void AstNodeGet::print(){
}
