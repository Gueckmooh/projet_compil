#include <string>
#include <map>
#include <vector>

#ifndef __ARM_ADDITION_H__
#define __ARM_ADDITION_H__

#include "arm_instruction.h"

using namespace std;

namespace arm {

  class arm_addition : public arm_instruction {
  public:
    arm_addition (void);
    ~arm_addition (void) {};

    virtual string get_instruction (void);
    virtual string get_op1 (void);
    virtual string get_op2 (void);
    virtual string get_op3 (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);
    virtual void set_op3 (string);
  protected:
    string op1;
    string op2;
    string op3;
  };

}

#endif //__ARM_ADDITION_H__
