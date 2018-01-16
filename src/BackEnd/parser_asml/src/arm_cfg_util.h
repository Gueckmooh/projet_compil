/**
 * \file      arm_addition.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Addition function implementation in ARM
 */

#ifndef __ARM_CFG_UTIL_H__
#define __ARM_CFG_UTIL_H__

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

#include "arm_cfg_node.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_addition
   *  \brief Contains the classes that manages the asml
   */
  class arm_cfg_util {
  public:
    /**
     * \brief  This function prints the control flow graph
     * \param  node the root of the graph to print
     */
    static void print_cfg (arm_cfg_node*);
  protected:
    static set<arm_cfg_node*> used; /*!< The set of node already used in the printing */
  };

}

#endif//__ARM_CFG_UTIL_H__
