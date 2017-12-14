#include <iostream>
#include <string>
#include "AstNodeGet.hpp"
#include "AstVisitor.hpp"


AstNodeGet::AstNodeGet(AstNode *t1, AstNode *t2){
    this->class_code = C_GET;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeGet::~AstNodeGet(){
    this->class_code = C_GET;
}

bool AstNodeGet::infer_types(){
    return true;
}

void AstNodeGet::print(){
}
