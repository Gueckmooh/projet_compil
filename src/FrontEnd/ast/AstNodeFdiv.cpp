#include <iostream>
#include "AstNodeFdiv.hpp"
#include "AstVisitor.hpp"
#include "config.h"


AstNodeFdiv::AstNodeFdiv(AstNode *t1, AstNode *t2){
    this->class_code = C_FDIV;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFdiv::~AstNodeFdiv(){
    this->class_code = C_FDIV;
}

bool AstNodeFdiv::infer_types(){
    return true;
}

void AstNodeFdiv::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "FDIV\n" << std::endl;
}
