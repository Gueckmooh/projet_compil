/**
 * \file      asml_instruction.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_instruction class
 */

#ifndef __ASML_INSTRUCTION_H__
#define __ASML_INSTRUCTION_H__

#include <string>
#include <iostream>

using namespace std;

/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {

  /*! \class asml_instruction
   *  \brief This class is defines the different interfaces for instructions in asml
   */
  class asml_instruction {
    friend class asml_factory;
  public:
    static const int FUNCALL = 1; /*! Instruction of type : Function Call */
    static const int AFFECTATION = 2; /*! Instruction of type : Affectation */
    static const int ADDITION = 3; /*! Instruction of type : Addition */
    static const int SOUSTRACTION = 4; /*! Instruction of type : Substraction */
    static const int CONDITION = 5; /*! Instruction of type : Condition */
    static const int NEGATION = 6; /*! Instruction of type : Negation */
    static const int MEM_NEW = 7; /*! Instruction of type : New Memory */
    static const int MEM_READ = 8; /*! Instruction of type : Memory Reading */
    static const int MEM_WRITE = 9; /*! Instruction of type : Memory Writing */
    static const int CLOSURE = 10; /*! Instruction of type : Closure */

    virtual ~asml_instruction (void) {};

    virtual int get_type (void);
    /**
     * \brief    This function generates the ASML code that correspond to this instruction
     * \details  This function is used to generate ASML code.
     * \param    ident an int that is the number of tabulations to insert to indent
     *           correctly the generated code
     * \return   a string containing the generated code
     */
    virtual string generate (int) = 0;
  protected:
    int type_id; /*! int of the instruction type */
  };

} 

#endif //__ASML_INSTRUCTION_H__
