#include <iostream>
#include <string>
#include "AstNodeLetRec.hpp"


AstNodeLetRec::AstNodeLetRec(FunDef *fun_def, AstNode *t1){
    this->fun_def = fun_def;
    this->t1 = t1;
}

AstNodeLetRec::~AstNodeLetRec(){}

bool AstNodeLetRec::infer_types(){
    return true;
}

void AstNodeLetRec::print(){
}
