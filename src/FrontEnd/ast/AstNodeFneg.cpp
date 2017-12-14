#include <iostream>
#include "AstNodeFneg.hpp"
#include "AstVisitor.hpp"


AstNodeFneg::AstNodeFneg(AstNode *t1){
    this->class_code = C_FNEG;
    this->t1 = t1;
}

AstNodeFneg::~AstNodeFneg(){
    this->class_code = C_FNEG;
}

bool AstNodeFneg::infer_types(){
    return true;
}

void AstNodeFneg::print(){
}
