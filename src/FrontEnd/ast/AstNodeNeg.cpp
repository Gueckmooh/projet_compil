#include <iostream>
#include "AstNodeNeg.hpp"
#include "config.h"


AstNodeNeg::AstNodeNeg(AstNode *t1){
    this->class_code = C_NEG;
    this->t1 = t1;
}

AstNodeNeg::~AstNodeNeg(){
    this->class_code = C_NEG;
}

bool AstNodeNeg::infer_types(){
    return true;
}

void AstNodeNeg::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "NEG\n" << std::endl;
}
