#include "arm_mem_create.h"

namespace arm {

  string arm_mem_create::get_instruction (void) {
    string instruction;
    switch (arm_util::type_of (size)) {
    case arm_util::DIRECT:
      instruction += "\tmov r0, #" + size + "\n";
      break;
    case arm_util::VARIABLE:
      instruction += "\tldr r0, [fp, #" + offset->find(size)->second + "]\n";
      break;
    default:
      break;
    }
    instruction += "\tbl __mem_new\n";
    instruction += "\tstr r0, [fp, #" + offset->find(op)->second + "]\n";
    return instruction;
  }

  void arm_mem_create::set_op (string op) {
    this->op = op;
  }

  void arm_mem_create::set_size (string size) {
    this->size = size;
  }

  string arm_mem_create::get_op (void) {
    return op;
  }

  string arm_mem_create::get_size (void) {
    return size;
  }

}
