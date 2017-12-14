#include "arm_instruction.h"
#include "arm_generator.h"

namespace arm {

  void arm_instruction::set_var_offset (map<string, string>* map) {
    this->offset = map;
  }

}
