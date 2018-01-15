/**
 * \file      asml_affectation.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Description breve du fichier
 *
 * \details    Description detaillee du fichier (non obligee)
 */

#ifndef __ASML_AFFECTATION_H__
#define __ASML_AFFECTATION_H__

#include <string>

#include "asml_instruction.h"

using namespace std;

/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {

  /*! \class   asml_affectation
   *  \brief   class that represents the affectation in asml
   *  \details it inherits from asml_instruction
   */
  class asml_affectation : public asml_instruction {
  public:
    asml_affectation (void);
    ~asml_affectation (void) {};

    virtual int get_type (void);
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
    string op1; /*! The first operand of the addition in let op1 = op2 in .. */
    string op2; /*! The second operand of the addition in let op1 = op2 in .. */
  };

}

#endif //__ASML_AFFECTATION_H__
