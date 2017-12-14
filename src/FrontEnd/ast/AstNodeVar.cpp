#include <iostream>
#include <string>
#include "AstNodeVar.hpp"


AstNodeVar::AstNodeVar(std::string var_name){
    this->var_name = var_name;
}

AstNodeVar::~AstNodeVar(){}

bool AstNodeVar::infer_types(){
    return true;
}

void AstNodeVar::print(){
}
