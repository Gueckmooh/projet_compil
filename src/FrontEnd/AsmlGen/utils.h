/**
 * \file      utils.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     contains useful functions used in the front end
 *
 * \details
 */
#ifndef UTILS_H
#define UTILS_H

#include "ast.h"
#include "list.h"

#define VARNAME_SIZE 16

#define ASML_FUNC_PREFIX "_min_caml_"

/**
 * \brief     duplicates the string src
 * \details
 * \param     src : the string to duplicate
 * \return    the copy of src
 */
char *cpy_str(char *src);

/**
 * \brief     generate a new variable name
 * \details
 * \param
 * \return    the pointer to the new variable name
 */
char *gen_varname();

/**
 * \brief     generate a new function name
 * \details
 * \param
 * \return    the pointer to the new function name
 */
char *gen_funcname();

/**
 * \brief     prefix the string funcname with "_min_caml_"
 * \details
 * \param     funcname : the string to prefix
 * \return    the prefixed string
 */
char *prefix_funcname(char *funcname);

/**
 * \brief     converts an integer in a newly allocated string
 * \details
 * \param     i : the integer to convert
 * \return    the resulting string
 */
char *int_to_str(int i);

/**
 * \brief     checks if the string starts with "_"
 * \details
 * \param     str : the string
 * \return    true if str is a label (ie starts with '_'), false otherwise
 */
bool is_a_label(char *str);

/**
 * \brief     finds a function definition in fd_list
 * \details
 * \param     label : the name of the function
 * \return    the function definition, or NULL if not found
 */
pfundef get_fd(char *label);

/**
 * \brief     allocates memory space for a function definition
 * \details
 * \param
 * \return    the pointer to the allocated memory
 */
pfundef alloc_fd();
#endif
