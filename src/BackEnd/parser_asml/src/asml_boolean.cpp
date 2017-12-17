#include "asml_boolean.h"

namespace asml {

  asml_boolean::asml_boolean (int type) {
    type_id = type;
  }

  int asml_boolean::get_type (void) {
    return type_id;
  }

  void asml_boolean::set_op1 (string op) {
    op1 = op;
  }

  void asml_boolean::set_op2 (string op) {
    op2 = op;
  }

  string asml_boolean::get_op1 (void) {
    return op1;
  }

  string asml_boolean::get_op2 (void) {
    return op2;
  }

}
