#include <string>
#include <list>
#include <map>
#include <functional>

#ifndef __ARM_CFG_ELEMENT_H__
#define __ARM_CFG_ELEMENT_H__

#include "arm_instruction.h"

using namespace std;

namespace arm {

  class arm_cfg_element {
    friend class arm_cfg_node;
  public:
    arm_cfg_element (arm_instruction*);
    list<string>::iterator vars_begin (void);
    list<string>::iterator vars_end (void);
    list<string>* get_vars (void);
    int get_nbregs (void);
    void set_callback (function<map<string, string>(void)>);
  protected:
    map<string, string> regs_maps;
    list<string> used_variables;
    map<string, int> scope;
    int nb_regs;
    arm_instruction* instruction;
  };

}

#endif //__ARM_CFG_ELEMENT_H__
