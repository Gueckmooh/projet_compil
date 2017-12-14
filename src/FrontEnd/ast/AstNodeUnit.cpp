#include <iostream>
#include "AstNodeUnit.hpp"


AstNodeUnit::AstNodeUnit(){}

AstNodeUnit::~AstNodeUnit(){}

bool AstNodeUnit::infer_types(){
    return true;
}

void AstNodeUnit::print(){}

void AstNodeUnit::traversal(AstVisitor *vis){
    vis->visit_node(this);
}
