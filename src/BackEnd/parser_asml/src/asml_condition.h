/**
 * \file      asml_condition.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_condition class
 */
#include <vector>
#include <string>

#ifndef __ASML_IF_H__
#define __ASML_IF_H__

#include "asml_instruction.h"
#include "asml_boolean.h"

using namespace std;
/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {
  /*! \class   asml_addition
   *  \brief   class that represent a condition in asml
   *  \details it inherits from asml_instruction
   */
  class asml_condition : public asml_instruction {
  public:
    asml_condition (void);
    ~asml_condition (void);

    virtual void set_var (string);
    virtual void set_boolean (asml_boolean*);
    virtual void add_then (asml_instruction*);
    virtual void add_else (asml_instruction*);

    virtual string get_var (void);
    virtual asml_boolean* get_boolean (void);
    virtual vector<asml_instruction*>* get_then (void);
    virtual vector<asml_instruction*>* get_else (void);
    /**
     * \brief    This function generates the ASML code that correspond to this instruction
     * \details  This function is used to generate ASML code.
     * \param    ident an int that is the number of tabulations to insert to indent
     *           correctly the generated code
     * \return   a string containing the generated code
     */
    virtual string generate (int);
  protected:
    string var; /*! name of the variable */
    asml_boolean* boolean; /* Boolean used in the condition */
    vector<asml_instruction*>* then_list; /* Vector of instructions executed in the then */
    vector<asml_instruction*>* else_list; /* Vector of instruction executed in the else */
  };

} 

#endif //__ASML_IF_H__
