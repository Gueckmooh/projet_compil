#include "arm_dom_node.h"

namespace arm {

  arm_dom_node::arm_dom_node (arm_cfg_node* node) {
    element = node;
  }

  void arm_dom_node::set_element (arm_cfg_node* node) {
    element = node;
  }

  arm_cfg_node* arm_dom_node::get_element (void) const {
    return element;
  }

  void arm_dom_node::add_succ (arm_dom_node* node) {
    succs.push_back(node);
  }

  vector<arm_dom_node*>* arm_dom_node::get_succs (void) const {
    return &succs;
  }

}
