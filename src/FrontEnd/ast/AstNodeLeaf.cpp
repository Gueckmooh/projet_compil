#include "AstVisitor.hpp"
#include "AstNodeLeaf.hpp"

AstNodeLeaf::AstNodeLeaf(){}

AstNodeLeaf::~AstNodeLeaf(){}

void AstNodeLeaf::traversal(AstVisitor *vis){
    vis->visit_node(this);
}
