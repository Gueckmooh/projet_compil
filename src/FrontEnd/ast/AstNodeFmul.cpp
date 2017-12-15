#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

#include <iostream>

AstNodeFmul::AstNodeFmul(AstNode *t1, AstNode *t2){
    this->class_code = C_FMUL;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFmul::~AstNodeFmul(){
    this->class_code = C_FMUL;
}

bool AstNodeFmul::infer_types(){
    return true;
}

void AstNodeFmul::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "FMUL\n" << std::endl;
}
