#include "asml_variable.h"

namespace asml {

  void asml_variable::set_name (string name) {
    this->name = name;
  }

  int asml_variable::get_type (void) {
    return type_id;
  }

  string asml_variable::get_name (void) const {
    return  name;
  }

}
