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
    static const int FUNCALL = 1;
    static const int AFFECTATION = 2;
    static const int ADDITION = 3;
    static const int SOUSTRACTION = 4;
    static const int CONDITION = 5;
    static const int NEGATION = 6;
    static const int MEM_NEW = 7;
    static const int MEM_READ = 8;
    static const int MEM_WRITE = 9;
    static const int CLOSURE = 10;

    virtual ~asml_instruction (void) {};

    virtual int get_type (void);
    virtual string generate (int) = 0;
  protected:
    int type_id;
  };

} // TODO

#endif //__ASML_INSTRUCTION_H__
