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


void AstVisPrint::visit_node(AstNode *node){
    // std::cout << "value of indent is " << indent << std::endl;
    this->indent ++;
    node->print(indent);
    this->indent --;
}

void AstVisPrint::visit_fun_def(FunDef * fun_def){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout <<"FUNDEF" << std::endl;
}
