#include <iostream>
#include "AstNodeLe.hpp"
#include "AstVisitor.hpp"


AstNodeLe::AstNodeLe(AstNode *t1, AstNode *t2){
    this->class_code = C_LE;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeLe::~AstNodeLe(){
    this->class_code = C_LE;
}

bool AstNodeLe::infer_types(){
    return true;
}

void AstNodeLe::print(){
}
