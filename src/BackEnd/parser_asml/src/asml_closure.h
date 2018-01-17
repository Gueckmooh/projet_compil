#include <string>
#include <vector>

#include "asml_instruction.h"

#ifndef __ASML_CLOSURE_H__
#define __ASML_CLOSURE_H__
/**
 * \file      asml_closure.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_closure class
 */

using namespace std;
/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {
  /*! \class   asml_closure
   *  \brief   class that represent a closure in asml
   *  \details it inherits from asml_instruction
   */
  class asml_closure : public asml_instruction {
  public:
    asml_closure (void);
    ~asml_closure (void) {};

    virtual string get_value (void);

    virtual void set_value (string);
    virtual void set_return (string);
    virtual void unset_return (void);
    virtual bool is_returning (void);
    virtual string get_retval (void);
    virtual void add_param (string);
    virtual vector<string>::iterator begin (void);
    virtual vector<string>::iterator end (void);

    /**
     * \brief    This function returns the number of parameters
     * \return   an int, the number of parameters
     */
    virtual int size (void);

    /**
     * \brief    This function returns the tth param
     * \param    t an int the index that we want to access
     * \return   a string the elemen at index t
     */
    virtual string operator[] (int);

    /**
     * \brief    This function generates the ASML code that correspond to this instruction
     * \details  This function is used to generate ASML code.
     * \param    ident an int that is the number of tabulations to insert to indent
     *           correctly the generated code
     * \return   a string containing the generated code
     */
    virtual string generate (int);
  protected:
    string value;           /*! Value of closure                     */
    string return_variable; /*! Return Variable of closure           */
    bool do_return;         /*! Boolean checking if there is something
                              returned from closure                   */
    vector<string> params;  /*! Vector of different parameters        */
  };

}

#endif //__ASML_CLOSURE_H__
