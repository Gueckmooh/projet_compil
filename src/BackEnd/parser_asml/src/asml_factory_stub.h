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
extern "C" void asml_create_function (void);
extern "C" void asml_set_function_name (char* name);
extern "C" void asml_add_int_param (char* var);
extern "C" void asml_add_int_variable (char* param);
extern "C" void asml_add_affectation (char* op1, char* op2);
extern "C" void asml_add_funcall (char* funcname, char* retval, char* params);
extern "C" void asml_add_addition (char* op1, char* op2, char* op3);
extern "C" void asml_add_soustraction (char* op1, char* op2, char* op3);
#else

void asml_create_function (void);
void asml_set_function_name (char* name);
void asml_add_int_param (char* var);
void asml_add_int_variable (char* param);
void asml_add_affectation (char* op1, char* op2);
void asml_add_funcall (char* funcname, char* retval, char* params);
void asml_add_addition (char* op1, char* op2, char* op3);
void asml_add_soustraction (char* op1, char* op2, char* op3);
#endif //__cplusplus

#endif //__ASML_FACTORY_STUB_H__
