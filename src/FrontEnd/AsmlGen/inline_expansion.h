/**
 * \file      inline_expansion.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     contains the functions used to apply inline expansion
 *
 * \details
 */

#ifndef _INLINE_EXPANSION_H_
#define _INLINE_EXPANSION_H_

#include "ast.h"

#define INLINE_THRESHOLD 4

/**
 * \brief     calculate the size of a function's body
 * \details
 * \param     t : the body of the function
 * \return    the size of the function's body
 */
int get_function_size(ptree t);

/**
 * \brief     applies inline expansion on the ptree t
 * \details
 * \param     t : the ptree to appply expansion to
 * \return    the modified ptree
 */
ptree apply_inline_expansion(ptree t);

/**
 * \brief     replace all calls to the function described in fd by its body in t
 * \details
 * \param     fd : the function definition whose body is to remove ; t : the ptree
 * \return    the modified ptree
 */
ptree replace_funcall_by_body(pfundef fd, ptree t);

/**
 * \brief     removes the function description fd from fd_list
 * \details
 * \param     fd : the fd to remove
 * \return
 */
void remove_fd_from_fd_list(pfundef fd);

/**
 * \brief     checks if a function is used as a variable in the ptree t
 * \details
 * \param     fd : the function definition ; t : the ptree
 * \return    true if it is used as a variable, false otherwise
 */
bool is_used_as_var(pfundef fd, ptree t);

#endif
