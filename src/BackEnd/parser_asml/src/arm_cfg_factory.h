/**
 * \file      arm_cfg_factory.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Definition of the arm control flow graph factory factory for arm generation
 */

#ifndef __ARM_CFG_FACTORY_H__
#define __ARM_CFG_FACTORY_H__

#include <string>
#include <vector>
#include <list>
#include <map>

#include "arm_cfg_node.h"
#include "arm_instruction.h"
#include "arm_condition.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_cfg_factory
   *  \brief The factory that construct arm controll flow graph
   */
  class arm_cfg_factory {
  public:

    /**
     * \brief  This function generate a control flow graph from a vector of arm instruction
     * \param  instructions the vector of instructions that is used to generate arm_cfg_node
     * \return an arm_cfg_node* te root of the controll flow graph used for optimization
     */
    static arm_cfg_node* generate_cfg (vector<arm_instruction*>*);
  protected:

    /**
     * \brief  This function generates a node of the control flow graph
     * \param  instructions a vector of arm_instruction* that is used for generation
     * \return an arm_cfg_node* that is the control flow graph node generated
     */
    static arm_cfg_node* generate_cfg_node (vector<arm_instruction*>*);
    static arm_cfg_node* root; /*!< the root of the currently generated cfg */
  };

}

#endif//__ARM_CFG_FACTORY_H__
