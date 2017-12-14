#include "asml.h"
#include "arm_util.h"
#include <string>
#include <map>
#include <vector>
#include <list>

#ifndef __ARM_INSTRUCION_H__
#define __ARM_INSTRUCION_H__

namespace arm {

  class arm_instruction {
    friend class arm_inst_factory;
  public:
    virtual string get_instruction (void) = 0;
    void set_var_offset (map<string, string>*);
  protected:
    map<string, string>* offset;
    vector<string> params;
  };

}

#endif //__ARM_INSTRUCION_H__
