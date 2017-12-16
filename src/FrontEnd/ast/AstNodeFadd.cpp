#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

#include <iostream>

AstNodeFadd::AstNodeFadd(AstNode *t1, AstNode *t2){
    this->class_code = C_FADD;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFadd::~AstNodeFadd(){
    this->class_code = C_FADD;
}

bool AstNodeFadd::infer_types(){
    return true;
}

void AstNodeFadd::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "FADD" << std::endl;
}
