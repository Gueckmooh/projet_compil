/**
 * \file      constant_folding.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     contains the functions used to apply constant_folding
 *
 * \details
 */
#ifndef _CONSTANT_FOLDING_H_
#define _CONSTANT_FOLDING_H_

#include <stdbool.h>

#include "ast.h"
#include "env.h"

/**
 * \brief     applies constant_folding to the ptree t
 * \details
 * \param     t : the ptree to which we want to apply constant_folding
 * \return    the resulting ptree
 */
ptree apply_constant_folding(ptree t);

/**
 * \brief     applies constant_folding to the ptree t recursively
 * \details
 * \param     t : the ptree to which we want to apply constant_folding ; env : the variable to integer environnement
 * \return    the resulting ptree
 */
ptree constant_folding(ptree t, env_node *env);

/**
 * \brief     tells if a variable can be folded
 * \details   a variable can be folded iff it's not used in a function call, a tuple or an array
 * \param     var_name : the concerned variable name ; t : the ptree to which we want to apply constant_folding
 * \return    true if the variable can be folded
 */
bool can_fold(char *var_name, ptree t);

ptree replace_var(ptree t, env_node *env);
#endif
