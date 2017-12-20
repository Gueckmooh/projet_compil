#include "asml_negation.h"

namespace asml {

  asml_negation::asml_negation (void) {
    type_id = asml_instruction::NEGATION;
  }

  string asml_negation::get_op1 (void) {
    return op1;
  }

  string asml_negation::get_op2 (void) {
    return op2;
  }

  void asml_negation::set_op1 (string op) {
    op1 = op;
  }

  void asml_negation::set_op2 (string op) {
    op2 = op;
  }

  string asml_negation::generate (int indent) {
    string ret;
    for (int i = 0; i < indent; i++)
      ret += "\t";
    if (op1.compare ("0") != 0)
      ret += "let " + op1 + " = ";
    ret += "neg " + op2;
    if (op1.compare ("0") != 0)
      ret += " in";
    ret += "\n";
    return ret;
  }


}
