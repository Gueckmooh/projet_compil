#include <iostream>
#include "AstNodeInt.hpp"


AstNodeInt::AstNodeInt(int i){
    this->i = i;
}

AstNodeInt::~AstNodeInt(){}

bool AstNodeInt::infer_types(){
    return true;
}

void AstNodeInt::print(){
}
