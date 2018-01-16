/**
 * \file      map_var_and_func.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     maps all variables used by functions and eliminates unnecessary defs
 *
 * \details
 */
#ifndef _MAP_VAR_AND_FUNC_H_
#define _MAP_VAR_AND_FUNC_H_

#include "ast.h"
#include "env.h"

/**
 * \brief     eliminates unnecessary defs from t and maps functions variables
 * \details
 * \param     t : the ptree
 * \return    the modified ptree
 */
ptree eliminate_unnecessary_defs(ptree t);

/**
 * \brief     eliminates unnecessary defs from t
 * \details
 * \param     t : the ptree
 * \return    the modified ptree
 */
ptree remove_unused_vars(ptree t);

/**
 * \brief     gets the list of all vars used in the ptree t
 * \details
 * \param     t : the ptree
 * \return    the list of all vars used in the ptree t
 */
plist get_list_of_vars_used(ptree t);

/**
 * \brief     gets the list of all vars created in the ptree t
 * \details
 * \param     t : the ptree
 * \return    the list of all vars created in the ptree t
 */
plist get_list_of_vars_created(ptree t);

/**
 * \brief     maps all functions variables
 * \details   separes variables in bounded or free variables
 * \param     t : the ptree ; env : the variable environnement
 * \return    the ptree modified (functions bodies have been extracted)
 */
ptree map_functions(ptree t, env_node *env);

#endif
