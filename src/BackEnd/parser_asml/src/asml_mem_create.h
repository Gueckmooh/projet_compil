/**
 * \file      asml_mem_create.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_mem_create class
 */

#include <string>

#ifndef __ASML_MEM_CREATE_H__
#define __ASML_MEM_CREATE_H__

#include "asml_instruction.h"

using namespace std;
/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {
  /*! \class   asml_mem_create
   *  \brief   class that represent a memory creation in asml
   *  \details it inherits from asml_instruction
   */
  class asml_mem_create : public asml_instruction {
  public:
    asml_mem_create (void);
    virtual ~asml_mem_create (void) {};
    /**
     * \brief    This function generates the ASML code that correspond to this instruction
     * \details  This function is used to generate ASML code.
     * \param    ident an int that is the number of tabulations to insert to indent
     *           correctly the generated code
     * \return   a string containing the generated code
     */
    virtual string generate (int);

    virtual void set_op (string);
    virtual void set_size (string);

    virtual string get_op (void);
    virtual string get_size (void);
  protected:
    string op; /*! Operand */
    string size; /*! Size of memory to allocate */
  };

} 

#endif //__ASML_MEM_CREATE_H__
