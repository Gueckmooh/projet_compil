/**
 * \file      duplicate.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     contains the functions used to duplicate a tree
 *
 * \details
 */
#ifndef _DUPLICATE_H_
#define _DUPLICATE_H_

#include "stdlib.h"

#include "list.h"
#include "ast.h"

/**
 * \brief     duplicates t
 * \details
 * \param     t : the ptree to duplicate
 * \return    the copy of t
 */
ptree duplicate_tree(ptree t);

/**
 * \brief     duplicates str
 * \details
 * \param     str : the string to duplicate
 * \return    the copy of str
 */
char *duplicate_string(char *str);

/**
 * \brief     duplicates a string list
 * \details
 * \param     l : the list of string to duplicate
 * \return    the copy of l
 */
plist duplicate_str_list(plist l);

/**
 * \brief     duplicates a list of ptrees
 * \details
 * \param     l : the list of ptrees to duplicate
 * \return    the copy of l
 */
plist duplicate_ptree_list(plist l);

/**
 * \brief     duplicates a funtion definition
 * \details
 * \param     fd : the fuinction definition to duplicate
 * \return    the copy of fd
 */
pfundef duplicate_fundef(pfundef fd);

#endif
