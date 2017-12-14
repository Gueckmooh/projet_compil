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

void AstNodeLetRec::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->fun_def->traversal(vis);
    this->t1->traversal(vis);
}
