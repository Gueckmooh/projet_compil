/**
 * \file      reduce_nested_let.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     applies nested let reduction
 *
 * \details
 */
#ifndef REDUCE_NESTED_LET_H
#define REDUCE_NESTED_LET_H

#include "ast.h"

/**
 * \brief     applies nested let reduction
 * \details
 * \param     t : the ptree
 * \return    the modified ptree
 */
ptree reduce_nested_let(ptree t);

#endif
