#include "asml_mem_read.h"

namespace asml {

  string asml_mem_read::generate (int indent) {
    string ret;
    for (int i = 0; i < indent; i++)
      ret += "\t";
    if (op.compare("0") != 0)
      ret += "let " + op + " = ";
    ret += "mem( " + mem_addr + " + " + mem_offset + ")";
    if (op.compare("0") != 0)
      ret += " in";
    ret += "\n";
    return ret;
  }

  void asml_mem_read::set_op (string op) {
    this->op = op;
  }

  void asml_mem_read::set_mem_offset (string mem_offser) {
    this->mem_offset = mem_offset;
  }

  void asml_mem_read::set_mem_addr (string mem_addr) {
    this->mem_addr = mem_addr;
  }

  string asml_mem_read::get_op (void) {
    return op;
  }

  string asml_mem_read::get_mem_offset (void) {
    return mem_offset;
  }

  string asml_mem_read::get_mem_addr (void) {
    return mem_addr;
  }

}
