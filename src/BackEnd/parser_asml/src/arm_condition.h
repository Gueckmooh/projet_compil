#include <string>
#include <map>
#include <vector>
#include <sstream>

#ifndef __ARM_CONDITION_H__
#define __ARM_CONDITION_H__

#include "arm_instruction.h"
#include "arm_boolean.h"

using namespace std;

namespace arm {

  class arm_condition : public arm_instruction {
  public:
    arm_condition (void);
    virtual ~arm_condition (void);

    virtual string get_instruction (void);

    virtual void set_var (string);
    virtual void add_then (arm_instruction*);
    virtual void add_else (arm_instruction*);
    virtual void set_boolean (arm_boolean*);
    virtual void set_lFalse (string);
    virtual void set_lFin (string);
    virtual void set_var_offset (map<string, string>*);
  protected:
    string var;
    arm_boolean* boolean;
    vector<arm_instruction*>* list_then;
    vector<arm_instruction*>* list_else;
    string lFalse;
    string lFin;
  };

}

#endif //__ARM_CONDITION_H__
