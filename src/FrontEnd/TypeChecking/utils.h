/**
 * \file      utils.h
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Some needed functions all-around
 * \details
 * this file defines utilitary functions such as
 * c_string to cpp_string,
 * c_string_list to cpp_string_list
 * c_ptree_list to cpp_AstNode_list
 * print_cpp_string_list
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "list.h"

class AstNode ;

std::string to_cpp_string(char * c_str);

std::vector<std::string> to_cpp_str_list(plist c_list);

std::vector<AstNode *> to_cpp_node_list(plist c_list);

void print_str_list(std::ostream& os, std::vector<std::string> str_list);

#endif	// UTILS_H

