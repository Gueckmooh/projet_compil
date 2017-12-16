#include "list.h"
#include "AstNode.hpp"
#include <string>
#include <list>

std::string to_cpp_string(char * c_str);

std::list<AstNode *> to_cpp_ast_list(plist c_list);

std::list<std::string> to_cpp_str_list(plist c_list);

void print_str_list(std::list<std::string> str_list);
