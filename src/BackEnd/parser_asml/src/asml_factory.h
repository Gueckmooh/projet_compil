#include <iostream>

#ifndef __ASML_FACTORY_H__
#define __ASML_FACTORY_H__

#include "asml_function.h"
#include "asml_integer.h"
#include "asml_affectation.h"
#include "asml_funcall.h"
#include "asml_addition.h"
#include "asml_soustraction.h"

using namespace std;

namespace asml {

  class asml_factory {
  public:
    static void initialize (void);
    static void validate_function (void);
    static vector<asml_function*>* get_function (void);
    static void set_function_name (string);
    static void add_int_param (vector<string>*);
    static void add_int_variable (string);
    static void add_affectation (string, string);
    static void add_funcall (string, string, vector<string>*);
    static void add_addition (string, string, string);
    static void add_soustraction (string, string, string);
  protected:
    static vector<asml_function*>* function_list;
    static asml_function* function;
  };

}

#endif //__ASML_FACTORY_H__
