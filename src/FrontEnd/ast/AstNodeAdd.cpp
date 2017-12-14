#include <iostream>
#include "AstNodeAdd.hpp"
#include "AstVisitor.hpp"
#include "config.h"

AstNodeAdd::AstNodeAdd(AstNode *t1, AstNode *t2){
    this->class_code = C_ADD;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeAdd::~AstNodeAdd(){
    this->class_code = C_ADD;
}

bool AstNodeAdd::infer_types(){
    return true;
}

void AstNodeAdd::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "PLUS\n" << std::endl;
}
