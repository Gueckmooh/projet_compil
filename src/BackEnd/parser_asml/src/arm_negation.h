/**
 * \file      arm_negation.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Negation instruction implementation in ARM
 *
 */

#ifndef __ARM_NEGATION_H__
#define __ARM_NEGATION_H__

#include <string>
#include <map>
#include <vector>

#include "arm_instruction.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {
  /*! \class arm_negation
   * \brief Negation instruction Object
   */
  class arm_negation : public arm_instruction {
  public:
    arm_negation (void);
    ~arm_negation (void) {};

    virtual string get_instruction (void);
    virtual string get_op1 (void);
    virtual string get_op2 (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);

    /**
     *  \brief Gives the number of registers used in this instruction
     *  \return an int, the number of register
     */
    virtual int nb_regs (void);

    /**
     * \brief  This function gives the list of operands of this instruction
     * \return list of string of operands
     */
    virtual list<string>* get_op_list (void);
  protected:
    string op1; /*!< first operand    */
    string op2; /*!< second operand   */
  };

}

#endif //__ARM_NEGATION_H__
