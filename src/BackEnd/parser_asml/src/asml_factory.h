#include <iostream>

#include "asml_function.h"
#include "asml_integer.h"
#include "asml_affectation.h"
#include "asml_funcall.h"

#ifndef __ASML_FACTORY_H__
#define __ASML_FACTORY_H__

using namespace std;

namespace asml {

  class asml_factory {
  public:
    static void create_function (void);
    static asml_function* get_function (void);
    static void set_function_name (string);
    static void add_int_param (string);
    static void add_int_variable (string, int);
    static void add_affectation (string, string);
    static void add_funcall (string, string, vector<string>*);
  protected:
    static asml_function* function;
  };

}

#endif //__ASML_FACTORY_H__
