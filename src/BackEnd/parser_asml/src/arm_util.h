#include <string>

using namespace std;

#ifndef __ARM_UTIL_H__
#define __ARM_UTIL_H__
/**
 * \file      arm_util.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     utility function for ARM generation
 *
 */
namespace arm {
/*! \class arm_util
 * \brief utils class
 */
  class arm_util {
  public:
    static const int DIRECT = 0; /*!< TODO            */
    static const int VARIABLE = 1; /*!< Variable type             */
    static const int LABEL = 2; /*!< Label Type              */
    static const int SELF = 3; /*!< TODO            */
    static int type_of (string); /*!< get type of ASML               */
  };

} // TODO

#endif //__ARM_UTIL_H__
