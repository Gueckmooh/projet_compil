#include "asml_mem_write.h"

namespace asml {

  asml_mem_write::asml_mem_write (void) {
    type_id = asml_instruction::MEM_WRITE;
  }

  string asml_mem_write::generate (int indent) {
    string ret;
    for (int i = 0; i < indent; i++)
      ret += "\t";
    if (op.compare("0") != 0)
      ret += "let " + op + " = ";
    ret += "mem( " + mem_addr + " + " + mem_offset + ")";
    ret += " <- " + value;
    if (op.compare("0") != 0)
      ret += " in";
    ret += "\n";
    return ret;
  }

  void asml_mem_write::set_op (string op) {
    this->op = op;
  }

  void asml_mem_write::set_mem_offset (string mem_offset) {
    this->mem_offset = mem_offset;
  }

  void asml_mem_write::set_mem_addr (string mem_addr) {
    this->mem_addr = mem_addr;
  }

  void asml_mem_write::set_value (string value) {
    this->value = value;
  }

  string asml_mem_write::get_op (void) {
    return op;
  }

  string asml_mem_write::get_mem_offset (void) {
    return mem_offset;
  }

  string asml_mem_write::get_mem_addr (void) {
    return mem_addr;
  }

  string asml_mem_write::get_value (void) {
    return value;
  }

}
