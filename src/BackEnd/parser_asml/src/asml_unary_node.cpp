#include "asml_unary_node.h"

namespace asml {

  asml_unary_node::asml_unary_node (void) {
    type_id = asml_node::UNARY;
  }

  asml_instruction* asml_unary_node::get_instruction (void) {
    return instruction;
  }

  asml_node* asml_unary_node::get_next (void) {
    return next;
  }

  void asml_unary_node::set_instruction (asml_instruction* instr) {
    instruction = instr;
  }

  void asml_unary_node::set_next (asml_node* node) {
    next = node;
  }

}
