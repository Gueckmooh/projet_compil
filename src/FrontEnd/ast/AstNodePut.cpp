#include <iostream>
#include <string>
#include "AstNodePut.hpp"
#include "config.h"


AstNodePut::AstNodePut(AstNode *t1, AstNode *t2, AstNode *t3){
    this->class_code = C_PUT;
    this->t1 = t1;
    this->t2 = t2;
    this->t3 = t3;
}

AstNodePut::~AstNodePut(){
    this->class_code = C_PUT;
}

bool AstNodePut::infer_types(){
    return true;
}

void AstNodePut::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "PUT\n" << std::endl;
}
