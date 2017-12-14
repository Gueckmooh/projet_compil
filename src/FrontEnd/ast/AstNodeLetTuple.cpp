#include <iostream>
#include <string>
#include "AstNodeLetTuple.hpp"


AstNodeLetTuple::AstNodeLetTuple(std::list<std::string> var_list,
                                 AstNode *t1,
                                 AstNode *t2){
    this->var_list = var_list;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeLetTuple::~AstNodeLetTuple(){}

bool AstNodeLetTuple::infer_types(){
    return true;
}

void AstNodeLetTuple::print(){
}

void AstNodeLetTuple::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
}
