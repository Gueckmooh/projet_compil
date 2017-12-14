#include <iostream>
#include <string>
#include "AstNodeApp.hpp"
#include "AstVisitor.hpp"

AstNodeApp::AstNodeApp(std::list<std::string> args_list, AstNode *t1){
    this->args_list = args_list;
    this->t1 = t1;
}

AstNodeApp::~AstNodeApp(){}

bool AstNodeApp::infer_types(){
    return true;
}

void AstNodeApp::print(){
}

void AstNodeApp::traversal(AstVisitor *vis){
    vis->visit_node(this);
    this->t1->traversal(vis);
}
