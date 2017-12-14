#include <string>

using namespace std;

#ifndef __ARM_UTIL_H__
#define __ARM_UTIL_H__

namespace arm {

  class arm_util {
  public:
    static const int DIRECT = 0;
    static const int VARIABLE = 1;
    static int type_of (string);
  };

}

#endif //__ARM_UTIL_H__
