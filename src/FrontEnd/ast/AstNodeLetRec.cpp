#include <iostream>
#include <string>
#include "AstNodeLetRec.hpp"
#include "config.h"


AstNodeLetRec::AstNodeLetRec(FunDef *fun_def, AstNode *t1){
    this->class_code = C_LETREC;
    this->fun_def = fun_def;
    this->t1 = t1;
}

AstNodeLetRec::~AstNodeLetRec(){
    this->class_code = C_LETREC;
}

bool AstNodeLetRec::infer_types(){
    return true;
}

void AstNodeLetRec::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "LETREC\n" << std::endl;
}

void AstNodeLetRec::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->fun_def->traversal(vis);
    this->t1->traversal(vis);
}
