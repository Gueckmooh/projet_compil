#include "AstNode.hpp"
#include "AstNodeLeaf.hpp"
#include "config.h"

#include <iostream>
#include <string>

AstNodeTuple::AstNodeTuple(std::list<AstNode *> var_list){
    this->class_code = C_TUPLE;
    this->var_list = var_list;
}

AstNodeTuple::~AstNodeTuple(){
    this->class_code = C_TUPLE;
}

bool AstNodeTuple::infer_types(){
    return true;
}

void AstNodeTuple::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "TUPLE\n" << std::endl;
}


void AstNodeTuple::traversal(AstVisitor *vis){
    vis->visit_node_start(this);
    for(std::list<AstNode *>::iterator i=this->var_list.begin() ; i != this->var_list.end() ; ++i){
        (*i)->traversal(vis);
    }
    vis->visit_node_end(this);
}
