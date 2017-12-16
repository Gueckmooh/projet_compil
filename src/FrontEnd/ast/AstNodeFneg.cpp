#include "AstNodeUnary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

#include <iostream>

AstNodeFneg::AstNodeFneg(AstNode *t1){
    this->class_code = C_FNEG;
    this->t1 = t1;
}

AstNodeFneg::~AstNodeFneg(){
    this->class_code = C_FNEG;
}

bool AstNodeFneg::infer_types(){
    return true;
}

void AstNodeFneg::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "FNEG" << std::endl;
}
