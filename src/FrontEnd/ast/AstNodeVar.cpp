#include <iostream>
#include <string>
#include "AstNodeVar.hpp"


AstNodeVar::AstNodeVar(std::string var_name){
    this->class_code = C_VAR;
    this->var_name = var_name;
}

AstNodeVar::~AstNodeVar(){
    this->class_code = C_VAR;
}

bool AstNodeVar::infer_types(){
    return true;
}

void AstNodeVar::print(){
}
