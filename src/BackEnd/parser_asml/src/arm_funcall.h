#include <string>
#include <map>
#include <vector>
#include <list>

#ifndef __ARM_FUNCALL_H__
#define __ARM_FUNCALL_H__

#include "arm_instruction.h"
/**
 * \file      arm_funcall.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Function calling implementation in ARM
 *
 */
namespace arm {
/*! \class arm_function
 * \brief function call Object
 */
  class arm_funcall : public arm_instruction {
  public:
    /*!
     *  \brief Constructor of the class arm_funcall
     *
     */
    arm_funcall (void);
    virtual string get_instruction (void);
    virtual void set_function_name (string);
    virtual void set_retval (string);
    virtual string get_retval (void);
    /*!
     *  \brief Number of Register
     *
     *  Return the number of registers
     *  \return int of register
     */
    virtual int nb_regs (void);
    /*!
     * \brief Getter of operands
     * Return the list of operands
     * \return list of string of operands
     */
    virtual list<string>* get_op_list (void);
    /*!
     * \brief TODO
     * \param instr string of instruction name
     * \return boolean
     */
    static bool immediate (string);
  protected:
    string function_name; /*!< function name              */
    bool is_returning; /*!< boolean to check if function return something              */
    string retval; /*!< return value name             */
  };

} // TODO

#endif //__ARM_FUNCALL_H__
