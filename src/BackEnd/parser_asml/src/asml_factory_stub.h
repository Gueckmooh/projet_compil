/**
 * \file      asml_addidition.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_addition class
 */

#ifndef __ASML_FACTORY_STUB_H__
#define __ASML_FACTORY_STUB_H__

#ifdef __cplusplus
#include <string>
#include <vector>
#include "asml_factory.h"
using namespace asml;
#endif //__cplusplus
#include <string.h>

#define ASML_NORMAL 0
#define ASML_THEN 1
#define ASML_ELSE 2
#define ASML_LT 3
#define ASML_GT 4
#define ASML_LE 5
#define ASML_GE 6
#define ASML_EQUAL 7

typedef struct {
  char* op1;
  char* op2;
  int type;
} asml_operation_t;

#ifdef __cplusplus
extern "C" void asml_validate_function (void);
extern "C" void asml_validate_condition (void);
extern "C" void asml_set_function_name (char* name);
extern "C" void asml_add_int_param (char* params);
extern "C" void asml_add_int_variable (char* param);
extern "C" void asml_add_affectation (char* op1, char* op2);
extern "C" void asml_add_funcall (char* funcname, char* retval, char* params);
extern "C" void asml_add_addition (char* op1, char* op2, char* op3);
extern "C" void asml_add_soustraction (char* op1, char* op2, char* op3);
extern "C" void asml_set_boolean (char* op1, char* op2, int type);
extern "C" void asml_set_next (int next);
#else

void asml_validate_function (void);
void asml_validate_condition (void);
void asml_set_function_name (char* name);
void asml_add_int_param (char* params);
void asml_add_int_variable (char* param);
void asml_add_affectation (char* op1, char* op2);
void asml_add_funcall (char* funcname, char* retval, char* params);
void asml_add_addition (char* op1, char* op2, char* op3);
void asml_add_soustraction (char* op1, char* op2, char* op3);
void asml_set_boolean (char* op1, char* op2, int type);
void asml_set_next (int next);
#endif //__cplusplus

// TODO

#endif //__ASML_FACTORY_STUB_H__
