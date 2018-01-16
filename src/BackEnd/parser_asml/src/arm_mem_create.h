/**
 * \file      arm_mem_create.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Memory creation in ARM
 *
 */

#ifndef __ARM_MEM_CREATE_H__
#define __ARM_MEM_CREATE_H__

#include <string>

#include "arm_instruction.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_mem_create
   * \brief Memory creation instruction Object
   */
  class arm_mem_create : public arm_instruction {
  public:
    ~arm_mem_create (void) {};

    virtual string get_instruction (void);

    virtual void set_op (string);
    virtual void set_size (string);

    virtual string get_op (void);
    virtual string get_size (void);

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
    string op;   /*!< operand        */
    string size; /*!< size of memory */
  };

}

#endif //__ARM_MEM_CREATE_H__
