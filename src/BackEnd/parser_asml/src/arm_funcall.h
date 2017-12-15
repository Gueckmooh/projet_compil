#include "arm_instruction.h"
#include <string>
#include <map>
#include <vector>
#include <list>

#ifndef __ARM_FUNCALL_H__
#define __ARM_FUNCALL_H__

namespace arm {

  class arm_funcall : public arm_instruction {
  public:
    virtual string get_instruction (void);
    virtual void set_function_name (string);
    static bool immediate (string);
  protected:
    string function_name;
  };

}

#endif //__ARM_FUNCALL_H__
