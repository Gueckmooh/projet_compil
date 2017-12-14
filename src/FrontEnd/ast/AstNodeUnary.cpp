#include "AstVisitor.hpp"
#include "AstNodeUnary.hpp"

AstNodeUnary::AstNodeUnary(){}

AstNodeUnary::AstNodeUnary(AstNode *t1){
    this->t1 = t1;
}

AstNodeUnary::~AstNodeUnary(){}

void AstNodeUnary::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
}
