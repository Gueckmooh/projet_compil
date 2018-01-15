#include <string>

#ifndef __ARM_MEM_CREATE_H__
#define __ARM_MEM_CREATE_H__

#include "arm_instruction.h"
/**
 * \file      arm_mem_create.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Memory creation in ARM
 *
 */
using namespace std;

namespace arm {
/*! \class arm_mem_create
 * \brief Memory creation instruction Object
 */
  class arm_mem_create : public arm_instruction {
  public:
    /*!
     *  \brief Destructor of the class mem_create
     *
     */
     ~arm_mem_create (void) {};

    virtual string get_instruction (void);

    virtual void set_op (string);
    virtual void set_size (string);

    virtual string get_op (void);
    virtual string get_size (void);
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
  protected:
    string op; /*!<      operand       */
    string size; /*!<     size of memory        */
  };

} // TODO

#endif //__ARM_MEM_CREATE_H__
