/**
 * \file      asml_parser_driver.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     This offers interface between C and C++ for parsing and generating ASML
 */

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
/**
 * \brief     This function creates an asml_function for the parsed function
 * \details   It uses the static function asml_factory::add_function
 * \param     func an asml_function_t that contains the function
 */
extern "C" void asml_parser_create_function (asml_function_t* func);

/**
 * \brief     This function creates an asml_asmt_t from the given datas
 * \details   This function is used to create the function tree
 * \param     op a char* that contains the operand of the instruction
 *            ex : let op = exp
 * \param     exp an amsl_asmt_t* that contains the expression for the asml_asmt_t
 *            es : let op = exp
 * \param     next an asml_asmt_t* the successor of the created node
 * \return    an asml_asmt_t* that contains the created node
 */
extern "C" asml_asmt_t* asml_parser_add_asmt (char* op, asml_exp_t* exp, asml_asmt_t* next);

/**
 * \brief     This function is used to create an asml_exp_t from the given datas
 * \details   This function is used to create an asmt node
 * \param     type an int, the type of the experssion. The types are defined in asml_parser_types.h
 * \param     op1 a void* the first operand of the expression
 * \param     op2 a void* the second operand of the expression
 * \param     op3 a void* the third operand of the expression
 * \return    an asml_exp_t* containing the created expression
 */
extern "C" asml_exp_t* asml_parser_create_exp (int type, void* op1, void* op2, void* op3);

/**
 * \brief     This function takes an argument and a list of argument to cocatenate them
 * \details   This function is used to create functon calls
 * \param     op a char*, the argument to concatenate
 * \param     next an asml_formal_arg_t* the list of argument that will follow op in the list
 * \return    A list of params given by the concatenation of op and next
 *            eg: asml_parser_add_arg (op, [op1, op2, op3]) -> [op, op1, op2, op3]
 */
extern "C" asml_formal_arg_t* asml_parser_add_arg (char* op, asml_formal_arg_t* next);

/**
 * \brief     This function converts an asml_exp_t* to an asml_boolean*
 * \details   This function is used to create the the asml_tree
 * \param     boolean an asml_exp_t* the expression containing the boolean
 * \return    an asml_boolean* that contains the boolean
 */
asml_boolean* asml_parser_create_boolean (asml_exp_t* boolean);

/**
 * \brief     This function set the params for the given instruction
 * \details   This function is used to construct an asml_funcall or an asml_closure
 * \param     args an asml_formal_arg_t* that contains the list of parameters to set in the function
 * \param     funcall an asml_instruction, it can be either an asml_funcall or an asml_closure,
 *            this instruction is the instruction in which we set the parameters
 */
void asml_parser_set_params (asml_formal_arg_t* args, asml_instruction* funcall);

/**
 * \brief     This function construct recursively an asml tree from an asml_asmt_t
 * \details   This function is used to transform the datas that is ceated by the front end
 *            or the parser to classes that is understandable by the backend
 * \param     asmt an asml_asmt_t* that is transformed by the function
 * \return    an asml_node*, the root of an asml tree that is understandable by the backend
 */
asml_node* asml_parser_create_tree (asml_asmt_t* asmt);

/**
 * \brief     This function creates an asml_function_t*
 * \details   This function is used by the parser for creating functons that can be used
 *            by asml_parser_create_function
 * \param     name a char*, the name of teh function to create
 * \param     args an amsl_formal_arg_t* the list of arguments taken by the function
 * \param     asmt an asml_asmt_t*, the asmt that composes the function
 * \return    an asml_function_t*  the created function
 */
extern "C" asml_function_t* asml_parser_package_function (char* name, asml_formal_arg_t* args, asml_asmt_t* asmt);
#else
void asml_parser_create_function (asml_function_t* func);
asml_asmt_t* asml_parser_add_asmt (char* op, asml_exp_t* exp, asml_asmt_t* next);
asml_exp_t* asml_parser_create_exp (int type, void* op1, void* op2, void* op3);
asml_formal_arg_t* asml_parser_add_arg (char* op, asml_formal_arg_t* next);
asml_function_t* asml_parser_package_function (char* name, asml_formal_arg_t* args, asml_asmt_t* asmt);
#endif

// TODO

#endif //__ASML_PARSER_DRIVER_H__
