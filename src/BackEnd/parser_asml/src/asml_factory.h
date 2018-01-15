#include <iostream>

#ifndef __ASML_FACTORY_H__
#define __ASML_FACTORY_H__

#include "asml_function.h"
#include "asml_integer.h"
#include "asml_affectation.h"
#include "asml_funcall.h"
#include "asml_addition.h"
#include "asml_soustraction.h"
#include "asml_condition.h"
#include "asml_negation.h"
#include "asml_node.h"
#include "asml_unary_node.h"
#include "asml_binary_node.h"
#include "asml_mem_create.h"
#include "asml_mem_read.h"
#include "asml_mem_write.h"
#include "asml_closure.h"

using namespace std;

namespace asml {

  class asml_factory {
  public:
    static const int NORMAL = 0;
    static const int THEN = 1;
    static const int ELSE = 2;

    static void initialize (void);
    static void validate_function (void);
    static void validate_condition (void);
    static void add_function (asml_function*, asml_node*);
    static vector<asml_function*>* get_function (void);
    static void set_function_name (string);
    static void add_int_param (string);
    static void add_int_variable (string);
    static void add_affectation (string, string);
    static void add_funcall (string, string, vector<string>*);
    static void add_addition (string, string, string);
    static void add_soustraction (string, string, string);
    static void set_boolean (string, string, int);
    static void append (asml_instruction*);
    static void set_next (int);
    static asml_instruction* create_instruction (asml_node*);
  protected:
    static int next;
    static vector<asml_function*>* function_list;
    static asml_function* function;
    static asml_condition* condition;
  };

} // TODO

#endif //__ASML_FACTORY_H__
