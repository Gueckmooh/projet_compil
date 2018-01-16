/**
 * \file      asml_integer.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_integer class
 */

#include <string>
#include "asml_variable.h"

#ifndef __ASML_INTEGER_H__
#define __ASML_INTEGER_H__

using namespace std;
/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {
  /*! \class   asml_integer
   *  \brief   class that represent an integer in asml
   *  \details it inherits from asml_variable
   */
  class asml_integer : public asml_variable {
  public:
    asml_integer (void);
    ~asml_integer (void) {};
  protected:
  };

} 

#endif //__ASML_INTEGER_H__
