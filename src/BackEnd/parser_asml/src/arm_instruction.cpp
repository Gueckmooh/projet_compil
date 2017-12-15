#include "arm_instruction.h"
#include "arm_generator.h"

namespace arm {

  void arm_instruction::set_var_offset (map<string, string>* map) {
    this->offset = map;
  }

  void arm_instruction::add_param (string param) {
    params.push_back(param);
  }

}
