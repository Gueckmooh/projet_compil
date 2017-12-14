#include <iostream>
#include <string>
#include "AstNodeTuple.hpp"


AstNodeTuple::AstNodeTuple(std::list<std::string> var_list){
    this->var_list = var_list;
}

AstNodeTuple::~AstNodeTuple(){}

bool AstNodeTuple::infer_types(){
    return true;
}

void AstNodeTuple::print(){
}
