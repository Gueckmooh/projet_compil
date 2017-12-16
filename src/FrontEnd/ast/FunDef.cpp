#include "FunDef.hpp"
#include "AstNode.hpp"
#include "utils.h"
#include <iostream>
#include <string>
#include <list>


FunDef::FunDef(
                    std::string var_name,
                    std::list<std::string> formal_args_list,
                    AstNode *body
                    ){
    this->var_name = var_name;
    this->formal_args_list = formal_args_list;
    this->body = body;
}

FunDef::~FunDef(){}

void FunDef::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "FUN_DEF name = "<< this->var_name <<"; args = ";
    print_str_list(this->formal_args_list);
    std::cout << std::endl;
}

void FunDef::traversal(AstVisitor *vis){
    vis->visit_fun_def_start(this);
    this->body->traversal(vis);
    vis->visit_fun_def_end(this);
}
