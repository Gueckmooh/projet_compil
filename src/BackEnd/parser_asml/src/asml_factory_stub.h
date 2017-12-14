#ifdef __cplusplus
#include <string>
#include <vector>
#include "asml_factory.h"
using namespace asml;
#endif //__cplusplus
#include <string.h>

#ifndef __ASML_FACTORY_STUB_H__
#define __ASML_FACTORY_STUB_H__

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
  void asml_create_function (void);
  void asml_set_function_name (char* name);
  void asml_add_int_param (char* var);
  void asml_add_int_variable (char* param, int value);
  void asml_add_affectation (char* op1, char* op2);
  void asml_add_funcall (char* funcname, char* retval, char* params);
#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__ASML_FACTORY_STUB_H__
