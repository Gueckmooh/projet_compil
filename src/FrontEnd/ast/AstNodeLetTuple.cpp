#include "AstNode.hpp"
#include "AstNodeBinary.hpp"
#include "config.h"

#include <iostream>
#include <string>

AstNodeLetTuple::AstNodeLetTuple(std::list<AstNode *> var_list,
                                 AstNode *t1,
                                 AstNode *t2){
    this->class_code = C_LETTUPLE;
    this->var_list = var_list;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeLetTuple::~AstNodeLetTuple(){
    this->class_code = C_LETTUPLE;
}

bool AstNodeLetTuple::infer_types(){
    return true;
}

void AstNodeLetTuple::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "TUPLE\n" << std::endl;
}
