#include "asml_soustraction.h"

namespace asml {

  asml_soustraction::asml_soustraction (void) {
    type_id = asml_instruction::SOUSTRACTION;
  }

  string asml_soustraction::get_op1 (void) {
    return op1;
  }

  string asml_soustraction::get_op2 (void) {
    return op2;
  }

  string asml_soustraction::get_op3 (void) {
    return op3;
  }

  void asml_soustraction::set_op1 (string op) {
    op1 = op;
  }

  void asml_soustraction::set_op2 (string op) {
    op2 = op;
  }

  void asml_soustraction::set_op3 (string op) {
    op3 = op;
  }

  string asml_soustraction::generate (int indent) {
    string ret;
    for (int i = 0; i < indent; i++)
      ret += "\t";
    if (op1.compare ("0") != 0)
      ret += "let " + op1 + " = ";
    ret += "sub " + op2 + " " + op3;
    if (op1.compare ("0") != 0)
      ret += " in";
    ret += "\n";
    return ret;
  }


}
