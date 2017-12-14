#include <iostream>
#include <string>
#include <list>
#include "FunDef.hpp"


FunDef::FunDef(
                    std::string var_name,
                    std::list<std::string> args_list,
                    AstNode *body
                    ){
    this->var_name = var_name;
    this->args_list = args_list;
    this->body = body;
}

FunDef::~FunDef(){}

void FunDef::traversal(AstVisitor *vis){
    vis->visit_fun_def(this);
    this->body->traversal(vis);
}
