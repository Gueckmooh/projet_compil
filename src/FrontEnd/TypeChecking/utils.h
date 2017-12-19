#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <list>
#include "list.h"

class AstNode ;

std::string to_cpp_string(char * c_str);

std::list<std::string> to_cpp_str_list(plist c_list);

std::list<AstNode *> to_cpp_node_list(plist c_list);

void print_str_list(std::ostream& os, std::list<std::string> str_list);

#endif	// UTILS_H

