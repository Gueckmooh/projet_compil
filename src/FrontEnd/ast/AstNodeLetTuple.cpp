#include <iostream>
#include <string>
#include "AstNodeLetTuple.hpp"


AstNodeLetTuple::AstNodeLetTuple(std::list<std::string> var_list,
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

void AstNodeLetTuple::print(){
}
