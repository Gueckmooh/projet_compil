#include <iostream>
#include "AstNodeFloat.hpp"


AstNodeFloat::AstNodeFloat(float b){
    this->f = f;
}

AstNodeFloat::~AstNodeFloat(){}

bool AstNodeFloat::infer_types(){
    return true;
}

void AstNodeFloat::print(){
}
