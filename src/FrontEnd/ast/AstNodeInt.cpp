#include <iostream>
#include "AstNodeInt.hpp"
#include "AstVisitor.hpp"

AstNodeInt::AstNodeInt(){}

AstNodeInt::AstNodeInt(int i){
    this->class_code = C_INT;
    this->i = i;
}

AstNodeInt::~AstNodeInt(){
    this->class_code = C_INT;
}

bool AstNodeInt::infer_types(){
    return true;
}

void AstNodeInt::print(){
}
