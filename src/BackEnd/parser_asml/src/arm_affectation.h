#include <string>
#include <map>
#include <vector>
#include <list>

#ifndef __ARM_AFFECTATION_H__
#define __ARM_AFFECTATION_H__

#include "arm_instruction.h"

namespace arm {

  class arm_affectation : public arm_instruction {
  public:
    arm_affectation (void);

    virtual string get_instruction (void);
    virtual void set_op1 (string);
    virtual void set_op2 (string);

    virtual string get_op1 (void);
    virtual string get_op2 (void);
  protected:
    string op1;
    string op2;
  };

}

#endif //__ARM_AFFECTATION_H__
