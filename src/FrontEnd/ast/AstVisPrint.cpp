#include "AstVisPrint.hpp"
#include "AstVisitor.hpp"
#include "FunDef.hpp"
#include "AstNode.hpp"
#include <iostream>
#include "config.h"

AstVisPrint::AstVisPrint(){
    this->next = NULL;
    this->indent = -1;
}

AstVisPrint::AstVisPrint(AstVisitor *next){
    this->next = next;
    this->indent = -1;
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

void AstVisPrint::visit_fun_def_start(FunDef * fun_def){
    if(this->next != NULL){
        this->next->visit_fun_def_start(fun_def);
    }
    this->indent ++;
    fun_def->print(indent);
}

void AstVisPrint::visit_fun_def_end(FunDef * fun_def){
    if(this->next != NULL){
        this->next->visit_fun_def_end(fun_def);
    }
    this->indent --;
}
