/**
 * \file      ast_to_asmlt.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     contains the functions used to translate a ptree structure into an asml_asmt_t structure
 *
 * \details
 */
#ifndef AST_TO_ASMLT_H
#define AST_TO_ASMLT_H

#include "asml_parser_types.h"
#include "ast.h"

#define _ALLOCATE_BYTES_
// if defined, call mem 4 to allocate an array of size 1 ; if not, call
// mem 1 to allocate an array of size 1.

#ifdef _ALLOCATE_BYTES_
    #define WORD_SIZE 4
#else
    #define WORD_SIZE 1
#endif

/**
 * \brief     translates a ptree structure with its functions definitions in an asml_asmt_t structure
 * \details   sends as well all functions definitions present in fd_list though send_func_d_to_asml_parser
 * \param     t : the ptree to convert
 * \return    the function "main"
 */
asml_function_t *build_asml_from_ptree(ptree t);

/**
 * \brief     translates a ptree in an asml_asmt_t structure
 * \details
 * \param     t : the ptree to convert
 * \return    the corresponding asml_asmt_t
 */
asml_asmt_t *to_asml_asmt(ptree t);

/**
 * \brief     translates a ptree in an asml_exp_t structure
 * \details
 * \param     t : the ptree to convert
 * \return    the corresponding asml_exp_t
 */
asml_exp_t *to_asml_exp(ptree t);

/**
 * \brief     translates a list of ptrees in a asml_formal_arg_t structure
 * \details
 * \param     ast_args_list : the list of trees to convert
 * \return    the corresponding asml_formal_arg_t
 */
asml_formal_arg_t *args_list_to_asml_args_list(plist ast_args_list);

/**
 * \brief     translates a list of string in a asml_formal_arg_t structure
 * \details
 * \param     ast_args_list : the list of string to convert
 * \return    the corresponding asml_formal_arg_t
 */
asml_formal_arg_t *string_list_to_asml_args_list(plist str_list);

/**
 * \brief     sends the function definition fd to the asml parser
 * \details
 * \param     fd : the function definition to send
 * \return
 */
void send_func_d_to_asml_parser(pfundef fd);

/**
 * \brief     translates a T_LETTUPLE ptree in an asml_asmt_t structure
 * \details
 * \param     t : the ptree to convert
 * \return    the corresponding asml_asmt_t
 */
asml_asmt_t *lettuple_to_asmlt(ptree t);

/**
 * \brief     translates a T_TUPLE ptree in an asml_asmt_t structure
 * \details
 * \param     t : the ptree to convert
 * \return    the corresponding asml_asmt_t
 */
asml_asmt_t *tuple_to_asml_asmt(ptree t);

/**
 * \brief     translates a T_MK_CLOS ptree in an asml_asmt_t structure
 * \details
 * \param     t : the ptree to convert
 * \return    the corresponding asml_asmt_t
 */
asml_asmt_t *mk_clos_to_asml_asmt(ptree t);

#endif
