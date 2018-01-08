#include <string>
#include <vector>

#ifndef __ARM_CLOSURE_H__
#define __ARM_CLOSURE_H__

#include "arm_instruction.h"
#include "arm_util.h"

using namespace std;

namespace arm {

  class arm_closure : public arm_instruction {
  public:
    arm_closure (void);
    ~arm_closure (void) {};

    string get_instruction (void);

    virtual string get_value (void);

    virtual void set_value (string);
    virtual void set_return (string);
    virtual void unset_return (void);
    virtual bool is_returning (void);
    virtual string get_retval (void);
    virtual void add_param (string);
    virtual vector<string>::iterator begin (void);
    virtual vector<string>::iterator end (void);
    virtual int size (void);
    virtual string operator[] (int);

    virtual int nb_regs (void);
    virtual list<string>* get_op_list (void);
  protected:
    string value;
    string return_variable;
    bool do_return;
    vector<string> params;
  };

}

#endif //__ARM_CLOSURE_H__
