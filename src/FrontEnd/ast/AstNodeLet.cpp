#include <iostream>
#include <string>
#include "AstNodeLet.hpp"


AstNodeLet::AstNodeLet(AstNode *t1, AstNode *t2, std::string var_name){
    this->t1 = t1;
    this->t2 = t2;
    this->var_name = var_name;
}

AstNodeLet::~AstNodeLet(){}

bool AstNodeLet::infer_types(){
    return true;
}

void AstNodeLet::print(){
}
