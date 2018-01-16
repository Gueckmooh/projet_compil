/**
 * \file      arm_funcall.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Function calling implementation in ARM
 */

#ifndef __ARM_FUNCALL_H__
#define __ARM_FUNCALL_H__

#include <string>
#include <map>
#include <vector>
#include <list>

#include "arm_instruction.h"

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {
  /*! \class arm_function
   * \brief function call Object
   */
  class arm_funcall : public arm_instruction {
  public:
    arm_funcall (void);
    virtual string get_instruction (void);
    virtual void set_function_name (string);
    virtual void set_retval (string);
    virtual string get_retval (void);

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

    /*!
     * \brief This function is used to know if a variable is an immediate or
     *        a label
     * \param instr string of operand name
     * \return boolean
     */
    static bool immediate (string);
  protected:
    string function_name;  /*!< function name                                 */
    bool is_returning;     /*!< boolean to check if function return something */
    string retval;         /*!< return value name                             */
  };

}

#endif //__ARM_FUNCALL_H__
