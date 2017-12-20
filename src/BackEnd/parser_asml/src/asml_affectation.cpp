#include "asml_affectation.h"

namespace asml {

  asml_affectation::asml_affectation (void) {
    type_id = asml_instruction::AFFECTATION;
  }

  int asml_affectation::get_type (void) {
    return type_id;
  }

  string asml_affectation::get_op1 (void) {
    return op1;
  }

  string asml_affectation::get_op2 (void) {
    return op2;
  }

  void asml_affectation::set_op1 (string op) {
    op1 = op;
  }

  void asml_affectation::set_op2 (string op) {
    op2 = op;
  }

  string asml_affectation::generate (int indent) {
    string ret;
    for (int i = 0; i < indent; i++)
      ret += "\t";
    if (op1.compare ("0") != 0)
      ret += "let " + op1 + " = ";
    ret += op2;
    if (op1.compare ("0") != 0)
      ret += " in";
    ret += "\n";
    return ret;
  }

}
