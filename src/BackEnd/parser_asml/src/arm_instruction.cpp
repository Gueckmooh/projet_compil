#include "arm_instruction.h"
#include "arm_generator.h"

namespace arm {

  int lien = 0;

  int arm_instruction::get_type (void) {
    return type_id;
  }

  void arm_instruction::set_var_offset (map<string, string>* map) {
    this->offset = map;
  }

  void arm_instruction::add_param (string param) {
    params.push_back(param);
  }

  void arm_instruction::set_callback (function<map<string, string>(void)> callback) {
    this->callback = callback;
  }

  vector<string> arm_instruction::get_used (void) {
    return params;
  }

}
