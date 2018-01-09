#include "arm_register_optimizer.h"

namespace arm {

  arm_regster_optimizer::arm_regster_optimizer (arm_dom_node* dom_root) {
    this->dom_root = dom_root;
  }

  arm_dom_node* arm_regster_optimizer::get_dom_root (void) {
    return dom_root;
  }

  void arm_regster_optimizer::set_dom_root (arm_dom_node*) {
    this->dom_root = dom_root;
  }

  void arm_regster_optimizer::optimize (void) {
    find_succs_variables (NULL);
  }

  void arm_regster_optimizer::find_succs_variables (arm_dom_node* node) {
    list<string>* node_vars;
    if (node == NULL) {
      already_visited.clear();
      for (auto& node: *dom_root->find_leafs()) {
	node_vars = node->element->get_vars();
	node->pred->add_succ_vars(node_vars);
	already_visited.push_back(node);
      }
      for (auto& node: *dom_root->find_leafs()) {
	if (node->pred != NULL)
	  find_succs_variables(node->pred);
      }
    }
    else {
      if ([&](){bool ret = false;
	  for (auto& e: already_visited)        // if node is not in already_visited
	    ret |= e == node;
	  return !ret;}()) {
	if (node->pred != NULL) {
	  node_vars = new list<string> (*node->succ_vars);
	  node_vars->splice(node_vars->end(), *node->element->get_vars());
	  node->pred->add_succ_vars (node_vars);
	}
      }
    }
  }

  void arm_regster_optimizer::find_preds_variables (arm_dom_node* node) {

  }

}
