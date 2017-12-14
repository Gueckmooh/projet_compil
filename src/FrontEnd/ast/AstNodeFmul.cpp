#include <iostream>
#include "AstNodeFmul.hpp"


AstNodeFmul::AstNodeFmul(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFmul::~AstNodeFmul(){}

bool AstNodeFmul::infer_types(){
    return true;
}

void AstNodeFmul::print(){
}
