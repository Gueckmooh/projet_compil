#include "arm_mem_read.h"

namespace arm {

  arm_mem_read::arm_mem_read (void) {
    type_id = arm_instruction::MEM_READ;
  }

  string arm_mem_read::get_instruction (void) {
    string instruction;
    instruction += "\tldr r0, [fp, #" + offset->find(mem_addr)->second + "]\n";
    switch (arm_util::type_of (mem_offset)) {
    case arm_util::DIRECT:
      instruction += "\tadd r0, r0, #" + mem_offset + "\n";
      instruction += "\tldr r1, [r0, #" + mem_offset + "]\n";
      break;
    case arm_util::VARIABLE:
      instruction += "\tldr r1, [fp, #" + offset->find(mem_offset)->second + "]\n";
      instruction += "\tadd r0, r0, r1\n";
      instruction += "\tldr r1, [r0]\n";
      break;
    default:
      break;
    }
    instruction += "\tstr r1, [fp, #" + offset->find(op)->second + "]\n";
    return instruction;
  }

  void arm_mem_read::set_op (string op) {
    this->op = op;
  }

  void arm_mem_read::set_mem_offset (string mem_offset) {
    this->mem_offset = mem_offset;
  }

  void arm_mem_read::set_mem_addr (string mem_addr) {
    this->mem_addr = mem_addr;
  }

  string arm_mem_read::get_op (void) {
    return op;
  }

  string arm_mem_read::get_mem_offset (void) {
    return mem_offset;
  }

  string arm_mem_read::get_mem_addr (void) {
    return mem_addr;
  }

}
