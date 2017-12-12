#include "asml_op.h"

asml_op::asml_op(int type) {
  type_id = type;
}

void asml_op::set_name (string name) {
  this->name = name;
}

void asml_op::set_val (int val) {
  this->val = val;
}

string asml_op::get_name (void) {
  return this->name;
}

int asml_op::get_val (void) {
  return this->val;
}

int asml_op::get_type (void) {
  return this->type_id;
}

string asml_op::to_string (void) {
  switch (type_id) {
  case FUNC:
    return name;
    break;
  case VAR:
    return std::to_string(get_val());
    break;
  case DIRECT:
    return name;
    break;
  default:
    return "";
  }
}
