/**
 * \file      asml_mem_write.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_mem_write class
 */
#include <string>

#ifndef __ASML_MEM_WRITE_H__
#define __ASML_MEM_WRITE_H__

#include "asml_instruction.h"
/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
using namespace std;

namespace asml {
 /*! \class   asml_mem_write
   *  \brief   class that represent memory writing in asml
   *  \details it inherits from asml_instruction
   */
  class asml_mem_write : public asml_instruction {
  public:
    asml_mem_write (void);
    virtual ~asml_mem_write (void) {};
    /**
     * \brief    This function generates the ASML code that correspond to this instruction
     * \details  This function is used to generate ASML code.
     * \param    ident an int that is the number of tabulations to insert to indent
     *           correctly the generated code
     * \return   a string containing the generated code
     */
    virtual string generate (int);

    virtual void set_op (string);
    virtual void set_mem_offset (string);
    virtual void set_mem_addr (string);
    virtual void set_value (string);

    virtual string get_op (void);
    virtual string get_mem_offset (void);
    virtual string get_mem_addr (void);
    virtual string get_value (void);
  protected:
    string op; /*! Operand */
    string mem_offset; /*! Offset of the memory */
    string mem_addr; /*! Address of the memory */
    string value; /*! Value of the memory to be written */
  };

} 

#endif //__ASML_MEM_WRITE_H__
