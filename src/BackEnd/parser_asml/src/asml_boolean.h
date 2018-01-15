/**
 * \file      asml_boolean.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_boolean class
 */

#ifndef __ASML_BOOLEAN_H__
#define __ASML_BOOLEAN_H__

#include <string>

using namespace std;

/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {

  /*! \class   asml_addition
   *  \brief   class that represent an addition in asml
   *  \details it inherits from asml_instruction
   */
  class asml_boolean {
  public:
    static const int LT = 3;
    static const int GT = 4;
    static const int LE = 5;
    static const int GE = 6;
    static const int EQUAL = 7;

    asml_boolean (int);
    virtual ~asml_boolean (void) {};

    virtual void set_op1 (string);
    virtual void set_op2 (string);

    virtual string get_op1 (void);
    virtual string get_op2 (void);

    virtual int get_type (void);

    virtual string generate (void);
  protected:
    int type_id;
    string op1;
    string op2;
  };

} // TODO

#endif //__ASML_BOOLEAN_H__
