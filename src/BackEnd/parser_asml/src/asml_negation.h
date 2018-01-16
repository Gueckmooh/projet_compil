/**
 * \file      asml_negation.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_negation class
 */

#include <string>
#include <iostream>

#ifndef __ASML_NEGATION_H__
#define __ASML_NEGATION_H__

#include "asml_instruction.h"

using namespace std;
/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {
  /*! \class   asml_negation
   *  \brief   class that represent a negation in asml
   *  \details it inherits from asml_instruction
   */
  class asml_negation : public asml_instruction {
  public:
    asml_negation (void);
    ~asml_negation (void) {};

    virtual string get_op1 (void);
    virtual string get_op2 (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);
    /**
     * \brief    This function generates the ASML code that correspond to this instruction
     * \details  This function is used to generate ASML code.
     * \param    ident an int that is the number of tabulations to insert to indent
     *           correctly the generated code
     * \return   a string containing the generated code
     */
    virtual string generate (int);
  protected:
    string op1; /*! The first operand of the negation */
    string op2; /*! The second operand of the negation */
  };

} 

#endif //__ASML_NEGATION_H__
