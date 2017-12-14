#include <iostream>
#include "AstNodeFadd.hpp"


AstNodeFadd::AstNodeFadd(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFadd::~AstNodeFadd(){}

bool AstNodeFadd::infer_types(){
    return true;
}

void AstNodeFadd::print(){
}
