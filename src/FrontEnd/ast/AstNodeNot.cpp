#include "AstNodeUnary.hpp"
#include "config.h"

#include <iostream>

AstNodeNot::AstNodeNot(AstNode *t1){
    this->class_code = C_NOT;
    this->t1 = t1;
}

AstNodeNot::~AstNodeNot(){
    this->class_code = C_NOT;
}

bool AstNodeNot::infer_types(){
    return true;
}

void AstNodeNot::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "NOT" << std::endl;
}
