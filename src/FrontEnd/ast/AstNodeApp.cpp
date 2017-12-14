#include <iostream>
#include <string>
#include "AstNodeApp.hpp"


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
