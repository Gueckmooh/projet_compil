#include "arm_affectation.h"

namespace arm {

  string arm_affectation::get_instruction (void) {
    string instruction;
    switch (arm_util::type_of(op2)) {
    case arm_util::DIRECT:
      instruction += "\tmov r0, #" + op2 + "\n";
      break;
    case arm_util::VARIABLE:
      instruction += "\tldr r0, [fp, #" + offset->find(op2)->second + "]\n";
      break;
    default:
      break;
    }
    instruction += "\tstr r0, [fp, #" + offset->find(op1)->second + "]\n";
    return instruction;
  }

  void arm_affectation::set_op1 (string op) {
    op1 = op;
  }

  void arm_affectation::set_op2 (string op) {
    op2 = op;
  }

  string arm_affectation::get_op1 (void) {
    return op1;
  }

  string arm_affectation::get_op2 (void) {
    return op2;
  }

}
