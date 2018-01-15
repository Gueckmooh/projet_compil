#include "arm_cfg_element.h"

namespace arm {

  arm_cfg_element::arm_cfg_element (arm_instruction* instr) {
    list<string>* l;
    instruction = instr;
    nb_regs = instr->nb_regs();
    l = instr->get_op_list();
    used_variables.merge(*l);
    delete l;
  }

  list<string>::iterator arm_cfg_element::vars_begin (void) {
    return used_variables.begin();
  }

  list<string>::iterator arm_cfg_element::vars_end (void) {
    return used_variables.end();
  }

  list<string>* arm_cfg_element::get_vars (void) {
    return new list<string> (used_variables);
  }

  int arm_cfg_element::get_nbregs (void) {
    nb_regs = instruction->nb_regs();
    return nb_regs;
  }

  void arm_cfg_element::set_callback (function<map<string, string>(void)> callback) {
    instruction->set_callback(callback);
  }

}
