#include <iostream>
#include "AstNodeIf.hpp"


AstNodeIf::AstNodeIf(AstNode *t1, AstNode *t2, AstNode *t3){
    this->t1 = t1;
    this->t2 = t2;
    this->t3 = t3;
}

AstNodeIf::~AstNodeIf(){}

bool AstNodeIf::infer_types(){
    return true;
}

void AstNodeIf::print(){
}
