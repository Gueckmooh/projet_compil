#include <string>

#ifndef __ARM_MEM_CREATE_H__
#define __ARM_MEM_CREATE_H__

#include "arm_instruction.h"

using namespace std;

namespace arm {

  class arm_mem_create : public arm_instruction {
    arm_mem_create (void);
    virtual ~arm_mem_create (void) {};

    virtual string generate (void);

    virtual void set_op (string);
    virtual void set_size (string);

    virtual string get_op (void);
    virtual string get_size (void);
  protected:
    string op;
    string size;
  };

}

#endif //__ARM_MEM_CREATE_H__
