#include "AstNodeUnary.hpp"
#include "AstVisitor.hpp"
#include "config.h"
#include "utils.h"

#include <iostream>
#include <string>

AstNodeApp::AstNodeApp(std::list<AstNode *> args_list, AstNode *t1){
    this->class_code = C_APP;
    this->args_list = args_list;
    this->t1 = t1;
}

AstNodeApp::~AstNodeApp(){
    this->class_code = C_APP;
}

bool AstNodeApp::infer_types(){
    return true;
}

void AstNodeApp::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "APP";
    std::cout << std::endl;
}

void AstNodeApp::traversal(AstVisitor *vis){
    vis->visit_node_start(this);
    this->t1->traversal(vis);
    for(std::list<AstNode *>::iterator i=this->args_list.begin() ; i != this->args_list.end() ; ++i){
        (*i)->traversal(vis);
    }
    vis->visit_node_end(this);
}
