#include <iostream>
#include "AstNodeLeaf.hpp"
#include "config.h"


AstNodeUnit::AstNodeUnit(){
    this->class_code = C_UNIT;
}

AstNodeUnit::~AstNodeUnit(){
    this->class_code = C_UNIT;
}

bool AstNodeUnit::infer_types(){
    return true;
}

void AstNodeUnit::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "UNIT\n" << std::endl;
}
