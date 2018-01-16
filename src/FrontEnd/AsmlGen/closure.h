/**
 * \file      closure.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     contains the functions used to apply closure conversion
 *
 * \details
 */
#ifndef _CLOSURE_H_
#define _CLOSURE_H_

#include "ast.h"
#include "list.h"
#include "env.h"

/**
 * \brief     applies closure conversion to the ptree t and to the functions definitions contained in fd_list
 * \details   also applies closure conversion to the functions definitions contained in fd_list
 * \param     t : the ptree to which we apply closure conversion
 * \return    t with modifications taking in account closure conversion
 */
ptree apply_closure_conversion(ptree t);

/**
 * \brief     applies closure conversion to the ptree t
 * \details
 * \param     t : the ptree to which we apply closure conversion
 * \return    t with modifications taking in account closure conversion
 */
ptree apply_clos(ptree t);

/**
 * \brief     adds lines of code to the function body to gather its free variables
 * \details
 * \param     fd : the function definition to modify ; current_var : recursion parameter ; offset : recursion parameter
 * \return    the modified body of fd
 */
ptree add_free_vars_refs(pfundef fd, listNode *current_var, int offset);
#endif
