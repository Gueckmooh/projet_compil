#include "AstNode.hpp"
#include "AstNodeBinary.hpp"
#include "config.h"
#include "utils.h"
#include <iostream>
#include <string>

AstNodeLetTuple::AstNodeLetTuple(std::list<std::string> var_list,
                                 AstNode *t1,
                                 AstNode *t2){
    this->class_code = C_LETTUPLE;
    this->var_list = var_list;
    this->t1 = t1;
    this->t2 = t2;
}

AstNodeLetTuple::~AstNodeLetTuple(){
    this->class_code = C_LETTUPLE;
}

bool AstNodeLetTuple::infer_types(){
    return true;
}

void AstNodeLetTuple::print(int indent){
    for (int i = 0 ; i < indent ; i++){
        std::cout << INDENT;
    }
    std::cout << "LET TUPLE args = ";
    print_str_list(this->var_list);
    std::cout << std::endl;
}

void AstNodeLetTuple::traversal(AstVisitor *vis){
    vis->visit_node_start(this);
    // for(std::list<AstNode *>::iterator i=this->var_list.begin() ; i != this->var_list.end() ; ++i){
    //     (*i)->traversal(vis);
    // }
    this->t1->traversal(vis);
    this->t2->traversal(vis);
    vis->visit_node_end(this);
}
