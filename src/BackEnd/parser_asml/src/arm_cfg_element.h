/**
 * \file      arm_cfg_element.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Definition of the arm control flow graph element for arm generation
 */

#ifndef __ARM_CFG_ELEMENT_H__
#define __ARM_CFG_ELEMENT_H__

#include <string>
#include <list>
#include <map>
#include <functional>

#include "arm_instruction.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_cfg_element
   *  \brief The elements that constitute the arm_cfg_node
   */
  class arm_cfg_element {
    friend class arm_cfg_node;
  public:
    arm_cfg_element (arm_instruction*);

    /**
     * \brief  This function gives an iterator to the begining of vars
     * \return a list<string>::iterator that is equal to vars.begin()
     */
    list<string>::iterator vars_begin (void);

    /**
     * \brief  This function gives an iterator to the begining of vars
     * \return a list<string>::iterator that is equal to vars.begin()
     */
    list<string>::iterator vars_end (void);
    list<string>* get_vars (void);

    /**
     * \brief  This function gives the number of register used in the instruction
     * \return an int, the number of registers
     */
    int get_nbregs (void);
  protected:
    map<string, string> regs_maps; /*!< the map between the variables and the registers    */
    list<string> used_variables;   /*!< The list of variables used by the instructon       */
    map<string, int> scope;        /*!< the map between a variable and its scope           */
    int nb_regs;                   /*!< the number of regs usable through this instruction */
    arm_instruction* instruction;  /*!< the instruction corresponding to this element      */
  };

}

#endif //__ARM_CFG_ELEMENT_H__
