#include "AstNodeLeaf.hpp"
#include "AstVisitor.hpp"
#include "config.h"

#include <iostream>

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

void AstNodeBool::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "BOOL"<< this->b << std::endl;
}
