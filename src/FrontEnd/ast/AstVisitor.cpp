#include "AstVisitor.hpp"
#include "AstNode.hpp"


AstVisitor::AstVisitor(){
    this->next = NULL;
}

AstVisitor::AstVisitor(AstVisitor *next){
    this->next = next;
}

AstVisitor::~AstVisitor(){}

void AstVisitor::visit_node(AstNode *node){
    if(this->next){
        this->next->visit_node(node);
    }
    // specific visitor code
}

void AstVisitor::visit_fun_def(FunDef *fun_def){
    if(this->next){
        this->next->visit_fun_def(fun_def);
    }
    // specific visitor code
}
