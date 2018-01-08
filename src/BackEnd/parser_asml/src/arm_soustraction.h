#include <string>
#include <map>
#include <vector>

#ifndef __ARM_SOUSTRACTION_H__
#define __ARM_SOUSTRACTION_H__

#include "arm_instruction.h"

using namespace std;

namespace arm {

  class arm_soustraction : public arm_instruction {
  public:
    arm_soustraction (void);
    ~arm_soustraction (void) {};

    virtual string get_instruction (void);
    virtual string get_op1 (void);
    virtual string get_op2 (void);
    virtual string get_op3 (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);
    virtual void set_op3 (string);

    virtual int nb_regs (void);
    virtual list<string>* get_op_list (void);
  protected:
    string op1;
    string op2;
    string op3;
  };

}

#endif //__ARM_SOUSTRACTION_H__
