#include <iostream>
#include "AstNodeEq.hpp"
#include "AstVisitor.hpp"


AstNodeEq::AstNodeEq(AstNode *t1, AstNode *t2){
    this->class_code = C_EQ;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeEq::~AstNodeEq(){
    this->class_code = C_EQ;
}

bool AstNodeEq::infer_types(){
    return true;
}

void AstNodeEq::print(){
}
