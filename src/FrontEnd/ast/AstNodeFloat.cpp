#include <iostream>
#include "AstNodeFloat.hpp"
#include "AstVisitor.hpp"
#include "config.h"


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

void AstNodeFloat::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "FLOAT\n" << std::endl;
}
