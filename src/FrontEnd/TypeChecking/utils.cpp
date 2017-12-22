#include "utils.h"
#include <string>
#include "list.h"
#include "ast.h"
#include "Ast.hpp"
#include <iostream>

inline std::string to_cpp_string(char * c_str){
    std::string s(c_str);
    return s;
}

std::list<std::string> to_cpp_str_list(plist c_list){
    std::list<std::string> cpp_list;
    char *c_str;
    listNode *node = c_list->head;
    while(node != NULL){
        c_str = (char *) node->data;
        cpp_list.push_back(to_cpp_string(c_str));
        node = node->next;
    }
    return cpp_list;
}

std::list<AstNode *> to_cpp_node_list(plist c_list){
    std::list<AstNode *> cpp_list;
    ptree t;
    listNode *node = c_list->head;
    while(node != NULL){
        t = (ptree) node->data;
        cpp_list.push_back(Ast::build_ast(t));
        node = node->next;
    }
    return cpp_list;
}

void print_str_list(std::ostream& os, std::list<std::string> str_list){
    for (std::list<std::string>::iterator i = str_list.begin() ;
         i != str_list.end() ; ++i) {
        os << *i << " ";
    }
}
