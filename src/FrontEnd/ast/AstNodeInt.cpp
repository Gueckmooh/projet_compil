#include "AstNodeLeaf.hpp"
#include "AstVisitor.hpp"
#include "config.h"

#include <iostream>

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

void AstNodeInt::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "INT value = "<< this->i << std::endl;
}
