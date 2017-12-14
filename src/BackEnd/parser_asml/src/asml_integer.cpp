#include "asml_integer.h"

namespace asml {

  asml_integer::asml_integer (void) {
    type_id = asml_variable::INTEGER;
    has_value = false;
  }

  void asml_integer::set_value (int value) {
    this->value = value;
    has_value = true;
  }

  void asml_integer::unset_value (void) {
    has_value = false;
  }

  bool asml_integer::has_value (void) {
    return has_value;
  }

  int asml_integer::get_value (void) {
    return value;
  }

}
