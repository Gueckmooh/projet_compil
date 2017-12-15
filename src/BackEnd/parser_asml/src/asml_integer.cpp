#include "asml_integer.h"

namespace asml {

  asml_integer::asml_integer (void) {
    type_id = asml_variable::INTEGER;
    has = false;
  }

  void asml_integer::set_value (int value) {
    this->value = value;
    has = true;
  }

  void asml_integer::unset_value (void) {
    has = false;
  }

  bool asml_integer::has_value (void) {
    return has;
  }

  int asml_integer::get_value (void) {
    return value;
  }

}
