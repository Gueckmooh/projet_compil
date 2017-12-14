#include <iostream>
#include "AstNodeFloat.hpp"
#include "AstVisitor.hpp"


AstNodeFloat::AstNodeFloat(float b){
    this->class_code = C_FLOAT;
    this->f = f;
}

AstNodeFloat::~AstNodeFloat(){
    this->class_code = C_FLOAT;
}

bool AstNodeFloat::infer_types(){
    return true;
}

void AstNodeFloat::print(){
}
