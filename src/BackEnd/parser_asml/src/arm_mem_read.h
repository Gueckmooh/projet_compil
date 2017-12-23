#include <string>

#ifndef __ARM_MEM_READ_H__
#define __ARM_MEM_READ_H__

#include "arm_instruction.h"

using namespace std;

namespace arm {

  class arm_mem_read : public arm_instruction {
  public:
    arm_mem_read (void);
    virtual ~arm_mem_read (void) {};

    virtual string get_instruction (void);

    virtual void set_op (string);
    virtual void set_mem_offset (string);
    virtual void set_mem_addr (string);

    virtual string get_op (void);
    virtual string get_mem_offset (void);
    virtual string get_mem_addr (void);
  protected:
    string op;
    string mem_offset;
    string mem_addr;
  };

}

#endif //__ARM_MEM_READ_H__
