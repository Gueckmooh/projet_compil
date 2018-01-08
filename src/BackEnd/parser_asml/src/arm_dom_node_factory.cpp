#include <iostream>
#include "arm_dom_node_factory.h"

namespace arm {

  arm_dom_node_factory::arm_dom_node_factory (arm_cfg_node* root) {
    cfg_root = root;
  }

  arm_dom_node* arm_dom_node_factory::generate (void) {
    get_succs(cfg_root);
    for (auto& e: succs)
      cout << "[" << e.first << " : " << e.second << "]" << endl;
    return NULL; // TODO
  }

  void arm_dom_node_factory::get_succs (arm_cfg_node* node) {
    if ((*(already_visited.find (node))) != node) {
      already_visited.insert (node);
      for (auto& e: *node->get_succs()) {
	succs.insert (pair<arm_cfg_node*, arm_cfg_node*> (node, e));
	get_succs (e);
      }
    }
  }

}
