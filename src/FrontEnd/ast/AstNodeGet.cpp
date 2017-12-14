#include <iostream>
#include <string>
#include "AstNodeGet.hpp"
#include "AstVisitor.hpp"
#include "config.h"


AstNodeGet::AstNodeGet(AstNode *t1, AstNode *t2){
    this->class_code = C_GET;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeGet::~AstNodeGet(){
    this->class_code = C_GET;
}

bool AstNodeGet::infer_types(){
    return true;
}

void AstNodeGet::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "GET\n" << std::endl;
}
