#include "AstNodeBinary.hpp"
#include "AstVisitor.hpp"

AstNodeBinary::AstNodeBinary(){}

AstNodeBinary::AstNodeBinary(AstNode *t1, AstNode *t2){
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeBinary::~AstNodeBinary(){}


void AstNodeBinary::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
    this->t2->traversal(vis);
}
