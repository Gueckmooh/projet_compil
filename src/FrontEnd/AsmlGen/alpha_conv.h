/**
 * \file      alpha_conv.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     applies alpha_conversion to the ptree given in argument
 *
 * \details
 */
#ifndef ALPHA_CONV_H
#define ALPHA_CONV_H

#include "ast.h"
#include "env.h"

/**
 * \brief     recursive function alpha-converting a ptree
 * \details   cf paper on mincaml compiler
 * \param     ptree : the ptree to alpha-convert ; env : the variable environnement
 * \return    the alpha_converted ptree
 */
ptree alpha_convert(ptree t, env_node *env);

/**
 * \brief     initialise a variable environnement
 * \details   includes mincaml library function such as print_int
 * \param
 * \return    an initialised environnement
 */
env_node *init_env();
#endif
