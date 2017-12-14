#include <iostream>
#include "AstNodeFadd.hpp"
#include "AstVisitor.hpp"


AstNodeFadd::AstNodeFadd(AstNode *t1, AstNode *t2){
    this->class_code = C_FADD;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFadd::~AstNodeFadd(){
    this->class_code = C_FADD;
}

bool AstNodeFadd::infer_types(){
    return true;
}

void AstNodeFadd::print(){
}
