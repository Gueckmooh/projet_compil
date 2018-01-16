/**
 * \file      arm_util.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     utility function for ARM generation
 *
 */

#ifndef __ARM_UTIL_H__
#define __ARM_UTIL_H__

#include <string>

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {
  /*! \class arm_util
   * \brief utils class
   */
  class arm_util {
  public:
    static const int DIRECT = 0;   /*!< The string is a direct value  */
    static const int VARIABLE = 1; /*!< The string is a variable name */
    static const int LABEL = 2;    /*!< The string is a label         */
    static const int SELF = 3;     /*!< The string is a %selg         */

    /**
     * \brief  This function returns a value following the 'type'
     *         given string
     * \param  param the string to 'evaluate'
     * \return an int in function of the 'type' of the variable
     */
    static int type_of (string);
  };

}

#endif //__ARM_UTIL_H__
