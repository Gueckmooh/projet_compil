#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

#include <iostream>
#include <string>

AstNodeArray::AstNodeArray(AstNode *t1, AstNode *t2){
    this->class_code = C_ARRAY;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeArray::~AstNodeArray(){
    this->class_code = C_ARRAY;
}

bool AstNodeArray::infer_types(){
    return true;
}

void AstNodeArray::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "ARRAY" << std::endl;
}
