#include <iostream>
#include "AstNodeFsub.hpp"
#include "AstVisitor.hpp"


AstNodeFsub::AstNodeFsub(AstNode *t1, AstNode *t2){
    this->class_code = C_FSUB;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFsub::~AstNodeFsub(){
    this->class_code = C_FSUB;
}

bool AstNodeFsub::infer_types(){
    return true;
}

void AstNodeFsub::print(){
}
