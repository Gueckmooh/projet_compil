/**
 * \file      asml_function.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_function class
 */

#include <iostream>
#include <string>
#include <vector>

#include "asml_variable.h"
#include "asml_instruction.h"

#ifndef __ASML_FUNCTON_H__
#define __ASML_FUNCTON_H__

using namespace std;
/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {
  /*! \class   asml_function
   *  \brief   class that represent a function in asml
   */
  class asml_function {
    friend class asml_factory;
  public:
    ~asml_function (void);

    virtual void set_name (string);
    virtual void add_param (asml_variable*);
    virtual void add_variable (asml_variable*);
    virtual void add_instruction (asml_instruction*);

    virtual string get_name (void);
    virtual vector<asml_variable*>::iterator variable_begin (void);
    virtual vector<asml_variable*>::iterator variable_end (void);
    virtual vector<asml_variable*>::iterator param_begin (void);
    virtual vector<asml_variable*>::iterator param_end (void);
    virtual vector<asml_instruction*>::iterator instruction_begin (void);
    virtual vector<asml_instruction*>::iterator instruction_end (void);
    virtual vector<asml_variable*>* get_variables (void);
    virtual vector<asml_variable*>* get_params (void);
    virtual vector<asml_instruction*>* get_instructions (void);
    /**
     * \brief    This function generates the ASML code that correspond to this instruction
     * \details  This function is used to generate ASML code.
     * \param    ident an int that is the number of tabulations to insert to indent
     *           correctly the generated code
     * \return   a string containing the generated code
     */
    virtual string generate (void);
  protected:
    string name; /*! Name of the function */
    vector<asml_variable*> variables; /*! Vector of different variables  */
    vector<asml_variable*> params; /*! Vector of different params*/
    vector<asml_instruction*> instructions; /*! Vector of different instructions */
  };

} 

#endif //__ASML_FUNCTON_H__
