#include <string>
#include <map>
#include <vector>
#include <list>

#ifndef __ARM_INSTRUCION_H__
#define __ARM_INSTRUCION_H__

#include "arm_util.h"

namespace arm {

  class arm_instruction {
  public:
    virtual ~arm_instruction (void) {};

    virtual string get_instruction (void) = 0;
    void set_var_offset (map<string, string>*);
    void add_param (string);
  protected:
    map<string, string>* offset;
    vector<string> params;
  };

}

#endif //__ARM_INSTRUCION_H__
