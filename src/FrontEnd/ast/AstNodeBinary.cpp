#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"
#include "config.h"
#include <iostream>

AstNodeBinary::AstNodeBinary(){}

AstNodeBinary::AstNodeBinary(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeBinary::~AstNodeBinary(){}

void AstNodeBinary::print(int indent){
    std::cout << "print called in AstBinary" << std::endl;
}

void AstNodeBinary::traversal(AstVisitor *vis){
    vis->visit_node_start(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
    vis->visit_node_end(this);
}
