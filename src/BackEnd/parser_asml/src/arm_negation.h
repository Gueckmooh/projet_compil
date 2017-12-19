#include <string>
#include <map>
#include <vector>

#ifndef __ARM_NEGATION_H__
#define __ARM_NEGATION_H__

#include "arm_instruction.h"

using namespace std;

namespace arm {

  class arm_negation : public arm_instruction {
  public:
    arm_negation (void);
    ~arm_negation (void) {};

    virtual string get_instruction (void);
    virtual string get_op1 (void);
    virtual string get_op2 (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);
  protected:
    string op1;
    string op2;
  };

}

#endif //__ARM_NEGATION_H__
