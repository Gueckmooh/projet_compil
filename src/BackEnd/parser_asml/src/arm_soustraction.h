/**
 * \file      arm_soustraction.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Substraction instruction implementation in ARM
 *
 */

#ifndef __ARM_SOUSTRACTION_H__
#define __ARM_SOUSTRACTION_H__

#include <string>
#include <map>
#include <vector>

#include "arm_instruction.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_soustraction
   * \brief Substraction instruction Object
   */
  class arm_soustraction : public arm_instruction {
  public:
    arm_soustraction (void);
    ~arm_soustraction (void) {};

    virtual string get_instruction (void);
    virtual string get_op1 (void);
    virtual string get_op2 (void);
    virtual string get_op3 (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);
    virtual void set_op3 (string);

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
    string op3; /*!< third operand    */
  };

}

#endif //__ARM_SOUSTRACTION_H__
