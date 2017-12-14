#include <iostream>
#include "AstNodeIf.hpp"
#include "AstVisitor.hpp"


AstNodeIf::AstNodeIf(AstNode *t1, AstNode *t2, AstNode *t3){
    this->class_code = C_IF;
    this->t1 = t1;
    this->t2 = t2;
    this->t3 = t3;
}

AstNodeIf::~AstNodeIf(){
    this->class_code = C_IF;
}

bool AstNodeIf::infer_types(){
    return true;
}

void AstNodeIf::print(){
}
