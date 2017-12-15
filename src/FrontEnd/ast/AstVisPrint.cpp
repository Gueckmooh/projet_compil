#include "AstVisPrint.hpp"
#include "AstVisitor.hpp"
#include "FunDef.hpp"
#include "AstNode.hpp"
#include <iostream>
#include "config.h"

AstVisPrint::AstVisPrint(){
    this->next = NULL;
    this->indent = 0;
}

AstVisPrint::AstVisPrint(AstVisitor *next){
    this->next = next;
    this->indent = 0;
}

AstVisPrint::~AstVisPrint(){}


void AstVisPrint::visit_node_start(AstNode *node){
    if(this->next != NULL){
        this->next->visit_node_start(node);
    }
    this->indent ++;
    node->print(indent);
}

void AstVisPrint::visit_node_end(AstNode *node){
    if(this->next != NULL){
        this->next->visit_node_end(node);
    }
    this->indent --;
}

void AstVisPrint::visit_binary_node1(AstNode *node){
    if(this->next != NULL){
        this->next->visit_binary_node1(node);
    }
}

void AstVisPrint::visit_ternary_node1(AstNode *node){
    if(this->next != NULL){
        this->next->visit_ternary_node1(node);
    }
}

void AstVisPrint::visit_ternary_node2(AstNode *node){
    if(this->next != NULL){
        this->next->visit_ternary_node2(node);
    }
}

void AstVisPrint::visit_fun_def(FunDef * fun_def){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout <<"FUNDEF" << std::endl;
}
