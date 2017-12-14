#include <iostream>
#include "AstNodeUnit.hpp"


AstNodeUnit::AstNodeUnit(){
    this->class_code = C_UNIT;
}

AstNodeUnit::~AstNodeUnit(){
    this->class_code = C_UNIT;
}

bool AstNodeUnit::infer_types(){
    return true;
}

void AstNodeUnit::print(){}
