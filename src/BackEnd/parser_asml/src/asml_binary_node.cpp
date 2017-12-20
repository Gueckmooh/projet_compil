#include "asml_binary_node.h"

namespace asml {

  asml_binary_node::asml_binary_node (void) {
    type_id = asml_node::BINARY;
  }

  string asml_binary_node::get_var (void) {
    return var;
  }

  asml_boolean* asml_binary_node::get_boolean (void) {
    return boolean;
  }

  asml_node* asml_binary_node::get_next_true (void) {
    return next_true;
  }

  asml_node* asml_binary_node::get_next_false (void) {
    return next_false;
  }

  void asml_binary_node::set_var (string var) {
    this->var = var;
  }

  void asml_binary_node::set_boolean (asml_boolean* boolean) {
    this->boolean = boolean;
  }

  void asml_binary_node::set_next_true (asml_node* node) {
    next_true = node;
  }

  void asml_binary_node::set_next_false (asml_node* node) {
    next_false = node;
  }

}
