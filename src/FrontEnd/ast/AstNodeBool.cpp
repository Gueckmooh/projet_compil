#include <iostream>
#include "AstNodeBool.hpp"


AstNodeBool::AstNodeBool(bool b){
    this->b = b;
}

AstNodeBool::~AstNodeBool(){}

bool AstNodeBool::infer_types(){
    return true;
}

void AstNodeBool::print(){
}
