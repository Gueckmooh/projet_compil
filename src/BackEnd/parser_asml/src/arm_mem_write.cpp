#include "arm_mem_write.h"

namespace arm {

  arm_mem_write::arm_mem_write (void) {
    type_id = arm_instruction::MEM_WRITE;
  }

  string arm_mem_write::get_instruction (void) {
    string instruction;
    switch (arm_util::type_of (mem_addr)) {
    case arm_util::VARIABLE:
      instruction += "\tldr r0, [fp, #" + offset->find(mem_addr)->second + "]\n";
      break;
    case arm_util::SELF:
      instruction += "\tmov r0, r6\n";
      break;
    default:
      break;
    }
    /*
    switch (arm_util::type_of (value)) {
    case arm_util::DIRECT:
      instruction += "\tmov r2, #" + value + "\n";
      break;
    case arm_util::VARIABLE:
      instruction += "\tldr r2, [fp, #" + offset->find(value)->second + "]\n";
    }
    switch (arm_util::type_of (mem_offset)) {
    case arm_util::DIRECT:
      instruction += "\tstr r2, [r0, #" + mem_offset + "]\n";
      break;
    case arm_util::VARIABLE:
      instruction += "\tldr r1, [fp, #" + offset->find(mem_offset)->second + "]\n";
      instruction += "\tadd r0, r0, r1\n";
      instruction += "\tstr r2, [r0]\n";
      break;
    default:
      break;
    }
    */
    if (arm_util::type_of(mem_offset) == arm_util::VARIABLE) {
      instruction += "\tldr r1, [fp, #" + offset->find(mem_offset)->second + "]\n";
      instruction += "\tadd r0, r0, r1\n";
    }
    switch (arm_util::type_of (value)) {
    case arm_util::DIRECT:
      instruction += "\tmov r1, #" + value + "\n";
      break;
    case arm_util::VARIABLE:
      instruction += "\tldr r1, [fp, #" + offset->find(value)->second + "]\n";
    }
    if (arm_util::type_of(mem_offset) == arm_util::DIRECT) {
      instruction += "\tstr r1, [r0, #" + mem_offset + "]\n";
    } else {
      instruction += "\tstr r1, [r0]\n";
    }
    return instruction;
  }

  void arm_mem_write::set_op (string op) {
    this->op = op;
  }

  void arm_mem_write::set_mem_offset (string mem_offset) {
    this->mem_offset = mem_offset;
  }

  void arm_mem_write::set_mem_addr (string mem_addr) {
    this->mem_addr = mem_addr;
  }

  void arm_mem_write::set_value (string value) {
    this->value = value;
  }

  string arm_mem_write::get_op (void) {
    return op;
  }

  string arm_mem_write::get_mem_offset (void) {
    return mem_offset;
  }

  string arm_mem_write::get_mem_addr (void) {
    return mem_addr;
  }

  string arm_mem_write::get_value (void) {
    return value;
  }

  int arm_mem_write::nb_regs (void) {
    return 2;
  }

  list<string>* arm_mem_write::get_op_list (void) {
    list<string>* l = new list<string> ();
    if (arm_util::type_of (mem_addr) == arm_util::VARIABLE)
      l->push_back(mem_addr);
    if (arm_util::type_of (mem_offset) == arm_util::VARIABLE)
      l->push_back(mem_offset);
    if (arm_util::type_of (value) == arm_util::VARIABLE)
      l->push_back(value);
    l->sort();
    return l;
  }

}
