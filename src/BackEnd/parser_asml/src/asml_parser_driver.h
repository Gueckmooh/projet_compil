#ifdef __cplusplus
#include <string>
#endif //__cplusplus

#ifndef __ASML_PARSER_DRIVER_H__
#define __ASML_PARSER_DRIVER_H__

#include "asml_parser_types.h"
#include "asml_factory_stub.h"
#ifdef __cplusplus
#include "asml_factory.h"

using namespace std;
using namespace asml;
#endif //__cplusplus


#ifdef __cplusplus
extern "C" void asml_parser_create_function (asml_function_t* func);
extern "C" asml_asmt_t* asml_parser_add_asmt (char* op, asml_exp_t* exp, asml_asmt_t* next);
extern "C" asml_exp_t* asml_parser_create_exp (int type, void* op1, void* op2, void* op3);
extern "C" asml_formal_arg_t* asml_parser_add_arg (char* op, asml_formal_arg_t* next);
asml_boolean* asml_parser_create_boolean (asml_exp_t* boolean);
void asml_parser_set_params (asml_formal_arg_t* args, asml_instruction* funcall);
asml_node* asml_parser_create_tree (asml_asmt_t* asmt);
extern "C" asml_function_t* asml_parser_package_function (char* name, asml_formal_arg_t* args, asml_asmt_t* asmt);
#else
void asml_parser_create_function (asml_function_t* func);
asml_asmt_t* asml_parser_add_asmt (char* op, asml_exp_t* exp, asml_asmt_t* next);
asml_exp_t* asml_parser_create_exp (int type, void* op1, void* op2, void* op3);
asml_formal_arg_t* asml_parser_add_arg (char* op, asml_formal_arg_t* next);
asml_function_t* asml_parser_package_function (char* name, asml_formal_arg_t* args, asml_asmt_t* asmt);
#endif

#endif //__ASML_PARSER_DRIVER_H__
