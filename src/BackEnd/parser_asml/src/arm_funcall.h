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
    arm_funcall (void);
    virtual string get_instruction (void);
    virtual void set_function_name (string);
    virtual void set_retval (string);
    virtual string get_retval (void);
    static bool immediate (string);
  protected:
    string function_name;
    bool is_returning;
    string retval;
  };

}

#endif //__ARM_FUNCALL_H__
