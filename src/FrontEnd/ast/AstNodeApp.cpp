#include <iostream>
#include <string>
#include "AstNodeApp.hpp"
#include "AstVisitor.hpp"

AstNodeApp::AstNodeApp(std::list<std::string> args_list, AstNode *t1){
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

void AstNodeApp::print(){
}
