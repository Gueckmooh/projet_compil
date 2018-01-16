/**
 * \file      arm_mem_read.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Memory Reading instruction implementation in ARM
 *
 */

#ifndef __ARM_MEM_READ_H__
#define __ARM_MEM_READ_H__

#include <string>

#include "arm_instruction.h"

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
using namespace std;

namespace arm {

  /*! \class arm_mem_read
   * \brief Memory Reading instruction Object
   */
  class arm_mem_read : public arm_instruction {
  public:
    arm_mem_read (void);
    virtual ~arm_mem_read (void) {};

    virtual string get_instruction (void);

    virtual void set_op (string);
    virtual void set_mem_offset (string);
    virtual void set_mem_addr (string);

    virtual string get_op (void);
    virtual string get_mem_offset (void);
    virtual string get_mem_addr (void);

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
    string op;         /*!< operands        */
    string mem_offset; /*!< memory offset   */
    string mem_addr;   /*!< memory address  */
  };

}

#endif //__ARM_MEM_READ_H__
