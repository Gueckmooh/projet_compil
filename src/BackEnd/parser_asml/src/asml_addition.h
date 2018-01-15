/**
 * \file      asml_addidition.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_addition class
 */

#ifndef __ASML_ADDITION_H__
#define __ASML_ADDITION_H__

#include <string>
#include <iostream>

#include "asml_instruction.h"

using namespace std;

/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {

  /*! \class   asml_addition
   *  \brief   class that represent an addition in asml
   *  \details it inherits from asml_instruction
   */
  class asml_addition : public asml_instruction {
  public:
    asml_addition (void);
    ~asml_addition (void) {};

    virtual string get_op1 (void);
    virtual string get_op2 (void);
    virtual string get_op3 (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);
    virtual void set_op3 (string);

    /**
     * \brief    This function generates the ASML code that correspond to this instruction
     * \details  This function is used to generate ASML code.
     * \param    ident an int that is the number of tabulations to insert to indent
     *           correctly the generated code
     * \return   a string containing the generated code
     */
    virtual string generate (int);
  protected:
    string op1;  /*! The first operand of the addition in let op1 = add op2 op3 in .. */
    string op2;  /*! The second operand of the addition in let op1 = add op2 op3 in .. */
    string op3;  /*! The third operand of the addition in let op1 = add op2 op3 in .. */
  };

}

#endif //__ASML_ADDITION_H__
