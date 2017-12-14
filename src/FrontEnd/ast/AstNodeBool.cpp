#include <iostream>
#include "AstNodeBool.hpp"
#include "AstVisitor.hpp"


AstNodeBool::AstNodeBool(bool b){
    this->b = b;
}

AstNodeBool::~AstNodeBool(){}

bool AstNodeBool::infer_types(){
    return true;
}

void AstNodeBool::print(){
}

void AstNodeBool::traversal(AstVisitor *vis){
    vis->visit_node(this);
}
