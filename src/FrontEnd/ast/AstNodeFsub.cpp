#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"

#include <iostream>

AstNodeFsub::AstNodeFsub(AstNode *t1, AstNode *t2){
    this->class_code = C_FSUB;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeFsub::~AstNodeFsub(){
    this->class_code = C_FSUB;
}

bool AstNodeFsub::infer_types(){
    return true;
}

void AstNodeFsub::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "FSUB\n" << std::endl;
}
