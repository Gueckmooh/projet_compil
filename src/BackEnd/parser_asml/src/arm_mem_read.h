#include <string>

#ifndef __ARM_MEM_READ_H__
#define __ARM_MEM_READ_H__

#include "arm_instruction.h"
/**
 * \file      arm_mem_read.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Memory Reading instruction implementation in ARM
 *
 */
using namespace std;

namespace arm {
/*! \class arm_mem_read
 * \brief Memory Reading instruction Object
 */
  class arm_mem_read : public arm_instruction {
  public:
    /*!
     *  \brief Constructor of the class arm_mem_read
     *
     */
    arm_mem_read (void);
    /*!
     *  \brief Destructor of the class arm_mem_read
     *
     */
    virtual ~arm_mem_read (void) {};

    virtual string get_instruction (void);

    virtual void set_op (string);
    virtual void set_mem_offset (string);
    virtual void set_mem_addr (string);

    virtual string get_op (void);
    virtual string get_mem_offset (void);
    virtual string get_mem_addr (void);
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
    string op; /*!<        operands     */
    string mem_offset; /*!<   memory offset          */
    string mem_addr; /*!<    memory address         */
  };

} // TODO

#endif //__ARM_MEM_READ_H__
