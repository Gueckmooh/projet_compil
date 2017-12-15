#include "AstVisitor.hpp"
#include "AstNode.hpp"
#include "config.h"

#include <iostream>

AstVisitor::AstVisitor(){
    this->next = NULL;
}

AstVisitor::AstVisitor(AstVisitor *next){
    this->next = next;
}

AstVisitor::~AstVisitor(){}

void AstVisitor::visit_node_start(AstNode *node){
    if(this->next){
        this->next->visit_node_start(node);
    }
    // specific visitor code
}

void AstVisitor::visit_node_end(AstNode *node){
    if(this->next){
        this->next->visit_node_end(node);
    }
    // specific visitor code
}

void AstVisitor::visit_binary_node1(AstNode *node){
    if(this->next){
        this->next->visit_binary_node1(node);
    }
    // specific visitor code
}

void AstVisitor::visit_ternary_node1(AstNode *node){
    if(this->next){
        this->next->visit_ternary_node1(node);
    }
    // specific visitor code
}

void AstVisitor::visit_ternary_node2(AstNode *node){
    if(this->next){
        this->next->visit_ternary_node2(node);
    }
    // specific visitor code
}

void AstVisitor::visit_fun_def(FunDef *fun_def){
    if(this->next){
        this->next->visit_fun_def(fun_def);
    }
    // specific visitor code
}
