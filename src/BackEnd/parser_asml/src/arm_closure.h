/**
 * \file      arm_closure.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Closure function implementation in ARM
 */

#ifndef __ARM_CLOSURE_H__
#define __ARM_CLOSURE_H__

#include <string>
#include <vector>

#include "arm_instruction.h"
#include "arm_util.h"

using namespace std;

namespace arm {
/*! \class arm_closure
 * \brief Closure instruction Object
 */
  class arm_closure : public arm_instruction {
  public:
    arm_closure (void);
    ~arm_closure (void) {};

    string get_instruction (void);

    virtual string get_value (void);

    virtual void set_value (string);
    virtual void set_return (string);
    virtual void unset_return (void);

    /*!
     *  \brief returns true if the function is returning a value
     *	\return boolean
     */
    virtual bool is_returning (void);

    virtual string get_retval (void);

    /*!
     *  \brief This function adds a parameter to the closure call
     *	\param param a string, the parameter to add
     */
    virtual void add_param (string);

    /*!
     *  \brief  This function returns an iterator to the begining of the begining
     *          the parameter vector
     *	\return a vector<string>::iterator the iterator to the begining of the
     *          parameter vector
     */
    virtual vector<string>::iterator begin (void);

      /*!
       *  \brief  This function returns an iterator to the end of the end
       *          the parameter vector
       *	\return a vector<string>::iterator the iterator to the end of the
       *          parameter vector
       */
    virtual vector<string>::iterator end (void);

    /*!
     *  \brief This function returns the size of the parameter vector
     *	\return an int, the size of the parameter vector
     */
    virtual int size (void);

    /*!
     *  \brief  This function return returns the element at the tth element of the
     *          parameter vector
     *  \param  t an int, the index of the wanted element
     *	\return a string, the wanted element
     */
    virtual string operator[] (int);

    /*!
     *  \brief This function gives the number of registers used by this instruction
     *  \return an int, the number of registers used in this instruction
     */
    virtual int nb_regs (void);

    /*!
     * \brief  This function gives the is of operands used in this instruction
     * \return a list of string of operands
     */
    virtual list<string>* get_op_list (void);
  protected:
    string value;           /*!< The name of te variable containing the first operand of
                              the closure call*/
    string return_variable; /*!< The variable in which store the returned value */
    bool do_return;         /*!< boolean checking if the function is teturning  */
    vector<string> params;  /*!< the parameter vector */
  };

}

#endif //__ARM_CLOSURE_H__
