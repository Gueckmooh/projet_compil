#include "asml_mem_create.h"

namespace asml {

  string asml_mem_create::generate (int indent) {
    string ret;
    for (int i = 0; i < indent; i++)
      ret += "\t";
    if (op.compare("0") != 0)
      ret += "let " + op + " = ";
    ret += "new " + size;
    if (op.compare("0") != 0)
      ret += " in";
    ret += "\n";
    return ret;
  }

  void asml_mem_create::set_op (string op) {
    this->op = op;
  }

  void asml_mem_create::set_size (string size) {
    this->size = size;
  }

  string asml_mem_create::get_op (void) {
    return op;
  }

  string asml_mem_create::get_size (void) {
    return size;
  }

}
