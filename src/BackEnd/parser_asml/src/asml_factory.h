#include <iostream>

#include "asml_function.h"

#ifndef __ASML_FACTORY_H__
#define __ASML_FACTORY_H__

using namespace std;

namespace asml {

  class asml_factory {
  public:
    virtual static void create_function (void);
    virtual static asml_function* get_function (void);
    virtual static void set_function_name (string);
    virtual static void add_int_param (string);
    virtual static void add_int_variable (string, int);
    virtual static void add_affectation (string, string);
    virtual static void add_funcall (string, string, vector<string>*);
  protected:
    static asml_function* function;
  };

}

#endif //__ASML_FACTORY_H__
