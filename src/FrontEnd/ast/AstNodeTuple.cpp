#include <iostream>
#include <string>
#include "AstNodeTuple.hpp"


AstNodeTuple::AstNodeTuple(std::list<std::string> var_list){
    this->class_code = C_TUPLE;
    this->var_list = var_list;
}

AstNodeTuple::~AstNodeTuple(){
    this->class_code = C_TUPLE;
}

bool AstNodeTuple::infer_types(){
    return true;
}

void AstNodeTuple::print(){
}
