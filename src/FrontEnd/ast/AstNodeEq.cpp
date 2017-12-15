#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

#include <iostream>

AstNodeEq::AstNodeEq(AstNode *t1, AstNode *t2){
    this->class_code = C_EQ;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeEq::~AstNodeEq(){
    this->class_code = C_EQ;
}

bool AstNodeEq::infer_types(){
    return true;
}

void AstNodeEq::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "EQ\n" << std::endl;
}
