#include <string>
#include <map>
#include <vector>

#ifndef __ARM_NEGATION_H__
#define __ARM_NEGATION_H__

#include "arm_instruction.h"
/**
 * \file      arm_negation.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Negation instruction implementation in ARM
 *
 */
using namespace std;

namespace arm {
/*! \class arm_negation
 * \brief Negation instruction Object
 */
  class arm_negation : public arm_instruction {
  public:
    /*!
     *  \brief Constructor of the class arm_negation
     *
     */
    arm_negation (void);
    /*!
     *  \brief Destructor of the class arm_negation
     *
     */
    ~arm_negation (void) {};

    virtual string get_instruction (void);
    virtual string get_op1 (void);
    virtual string get_op2 (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);
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
    string op1;/*!< first operand              */
    string op2;/*!< second operand              */
  };

} // TODO

#endif //__ARM_NEGATION_H__
