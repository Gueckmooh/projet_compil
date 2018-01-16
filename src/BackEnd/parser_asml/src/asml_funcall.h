/**
 * \file      asml_funcall.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_funcall class
 */
#include <string>
#include <vector>

#include "asml_instruction.h"

#ifndef __ASML_FUNCALL_H__
#define __ASML_FUNCALL_H__

using namespace std;
/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {
  /*! \class   asml_funcall
   *  \brief   class that represent a function call in asml
   *  \details it inherits from asml_instruction
   */
  class asml_funcall : public asml_instruction {
  public:
    asml_funcall (void);
    ~asml_funcall (void) {};

    virtual string get_funcname (void);

    virtual void set_funcname (string);
    virtual void set_return (string);
    virtual void unset_return (void);
    virtual bool is_returning (void);
    virtual string get_retval (void);
    virtual void add_param (string);
    virtual vector<string>::iterator begin (void);
    virtual vector<string>::iterator end (void);
    /**
     * \brief    TODO
     * \return   an int TODO
     */
    virtual int size (void);
    /**
     * \brief    TODO
     * \param    t an int TODO
     * \return   a string containing the generated code
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
    string funcname; /*! The name of the function */
    string return_variable; /*! The returning variable */
    bool do_return; /*! A boolean that checks if a variable is returning */
    vector<string> params; /*! A vector of parameters */
  };

} // TODO

#endif //__ASML_FUNCALL_H__
