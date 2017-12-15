#include "asml_addition.h"

namespace asml {

  asml_addition::asml_addition (void) {
    type_id = asml_instruction::ADDITION;
  }

  string asml_addition::get_op1 (void) {
    return op1;
  }

  string asml_addition::get_op2 (void) {
    return op2;
  }

  string asml_addition::get_op3 (void) {
    return op3;
  }

  void asml_addition::set_op1 (string op) {
    op1 = op;
  }

  void asml_addition::set_op2 (string op) {
    op2 = op;
  }

  void asml_addition::set_op3 (string op) {
    op3 = op;
  }

}
