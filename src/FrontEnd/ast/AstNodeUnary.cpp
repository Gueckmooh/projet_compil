#include "AstVisitor.hpp"
#include "AstNodeUnary.hpp"
#include "config.h"

AstNodeUnary::AstNodeUnary(){}

AstNodeUnary::AstNodeUnary(AstNode *t1){
    this->t1 = t1;
}

AstNodeUnary::~AstNodeUnary(){}

void AstNodeUnary::traversal(AstVisitor *vis){
    vis->visit_node_start(this);
    this->t1->traversal(vis);
    vis->visit_node_end(this);
}
