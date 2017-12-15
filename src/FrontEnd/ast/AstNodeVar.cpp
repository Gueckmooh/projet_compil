#include "AstNodeLeaf.hpp"
#include "config.h"

#include <iostream>
#include <string>

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

void AstNodeVar::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "VAR " << this->var_name << std::endl;
}
