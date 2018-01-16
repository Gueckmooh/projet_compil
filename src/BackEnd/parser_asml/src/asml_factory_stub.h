/**
 * \file      asml_factory_stub.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_factory_stub class
 */

#ifdef __cplusplus
#include <string>
#include <vector>
#include "asml_factory.h"
using namespace asml;
#endif //__cplusplus
#include <string.h>
/*!
  \def ASML_NORMAL
  \brief Normal ASML case
*/
#define ASML_NORMAL 0
/*!
  \def ASML_THEN
  \brief ASML then case
*/
#define ASML_THEN 1
/*!
  \def ASML_ELSE
  \brief ASML else case
*/
#define ASML_ELSE 2
/*!
  \def ASML_LT
  \brief ASML less than
*/
#define ASML_LT 3
/*!
  \def ASML_GT
  \brief ASML Greater Than
*/
#define ASML_GT 4
/*!
  \def ASML_LE
  \brief ASML Less or Equal
*/
#define ASML_LE 5
/*!
  \def ASML_GE
  \brief ASML Greater or Equal
*/
#define ASML_GE 6
/*!
  \def ASML_EQUAL
  \brief ASML Equality
*/
#define ASML_EQUAL 7

#ifndef __ASML_FACTORY_STUB_H__
#define __ASML_FACTORY_STUB_H__

typedef struct {
  char* op1; /*!< first operand              */
  char* op2; /*!< second operand              */
  int type; /*!< type              */
} asml_operation_t;

#ifdef __cplusplus
//extern "C" void asml_create_function (void);
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

//void asml_create_function (void);
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
