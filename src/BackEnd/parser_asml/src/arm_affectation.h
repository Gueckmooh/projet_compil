/**
 * \file      arm_addition.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Affectation function implementation in ARM
 */

#ifndef __ARM_AFFECTATION_H__
#define __ARM_AFFECTATION_H__

#include <string>
#include <map>
#include <vector>
#include <list>

#include "arm_instruction.h"

namespace arm {
/*! \class arm_affectation
 *  \brief Affectation instruction Object
 */
  class arm_affectation : public arm_instruction {
  public:
    arm_affectation (void);

    virtual string get_instruction (void);
    virtual void set_op1 (string);
    virtual void set_op2 (string);

    virtual string get_op1 (void);
    virtual string get_op2 (void);

    /*!
     *  \brief Gives the number of registers used in this instruction
     *  \return an int, the number of register
     */
    virtual int nb_regs (void);

    /*!
     * \brief  This function gives the list of operands of this instruction
     * \return list of string of operands
     */
    virtual list<string>* get_op_list (void);
  protected:
    string op1;/*!< first operand  */
    string op2;/*!< second operand */
  };

}

#endif //__ARM_AFFECTATION_H__
