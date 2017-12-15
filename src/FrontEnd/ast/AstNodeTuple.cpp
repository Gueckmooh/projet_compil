#include "AstNodeLeaf.hpp"
#include "config.h"

#include <iostream>
#include <string>

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

void AstNodeTuple::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "TUPLE\n" << std::endl;
}
