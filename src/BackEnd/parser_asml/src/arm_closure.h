#include <string>
#include <vector>

#ifndef __ARM_CLOSURE_H__
#define __ARM_CLOSURE_H__

#include "arm_instruction.h"
#include "arm_util.h"
/**
 * \file      arm_closure.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Closure function implementation in ARM
 *
 */
using namespace std;

namespace arm {
/*! \class arm_closure
 * \brief Closure instruction Object
 */
  class arm_closure : public arm_instruction {
  public:
    /*!
     *  \brief Constructor of the class arm_closure
     */
    arm_closure (void);
    /*!
     *  \brief Destructor of the class arm_closure
     *
     */
    ~arm_closure (void) {};

    string get_instruction (void);

    virtual string get_value (void);

    virtual void set_value (string);
    virtual void set_return (string);
    virtual void unset_return (void);
    /*!
     *  \brief TODO
     *	\return boolean
     */
    virtual bool is_returning (void);

    virtual string get_retval (void);

    /*!
     *  \brief TODO
     *	\param string param
     */
    virtual void add_param (string);
    /*!
     *  \brief TODO
     *	\return TODO
     */
    virtual vector<string>::iterator begin (void);
    /*!
     *  \brief TODO
     *	\return TODO
     */
    virtual vector<string>::iterator end (void);
    /*!
     *  \brief size getter
     *	\return int size
     */
    virtual int size (void);
    /*!
     *  \brief TODO
     *  \param int t 
     *	\return element t of params array 
     */
    virtual string operator[] (int);
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
    string value; /*!< value             */
    string return_variable; /*!< return value              */
    bool do_return; /*!< boolean checking there is a return             */
    vector<string> params; /*!< parameter vector              */
  };

}

#endif //__ARM_CLOSURE_H__
