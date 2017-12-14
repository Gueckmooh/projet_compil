#include <iostream>
#include "AstNodeBool.hpp"
#include "AstVisitor.hpp"


AstNodeBool::AstNodeBool(bool b){
    this->class_code = C_BOOL;
    this->b = b;
}

AstNodeBool::~AstNodeBool(){
    this->class_code = C_BOOL;
}

bool AstNodeBool::infer_types(){
    return true;
}

void AstNodeBool::print(){
}
