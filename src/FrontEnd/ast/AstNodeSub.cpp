#include <iostream>
#include "AstNodeSub.hpp"
#include "config.h"


AstNodeSub::AstNodeSub(AstNode *t1, AstNode *t2){
    this->class_code = C_SUB;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeSub::~AstNodeSub(){
    this->class_code = C_SUB;
}

bool AstNodeSub::infer_types(){
    return true;
}

void AstNodeSub::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "SUB\n" << std::endl;
}
