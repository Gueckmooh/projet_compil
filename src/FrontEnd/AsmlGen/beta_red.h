/**
 * \file      beta_red.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     contains the function used to apply beta reduction
 *
 * \details
 */
#ifndef _BETA_RED_H_
#define _BETA_RED_H_

#include "ast.h"
#include "env.h"

/**
 * \brief     applies beta reduction to the ptree t
 * \details   beta converts, but takes care to appply beta conversion to variables only, not to labels
 * \param     t : the ptree to beta-convert
 * \return    the beta-reduced ptree
 */
ptree beta_red(ptree t, env_node *env);

#endif
