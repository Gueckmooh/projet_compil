#include "arm_util.h"

namespace arm {

  int arm_util::type_of (string param) {
    char c = param.front();
    if (c >= '0' && c <= '9')
      return DIRECT;
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
      return VARIABLE;
    else
      return -1;
  }

}
