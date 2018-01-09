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

  void arm_dom_node::set_pred (arm_dom_node* node) {
    pred = node;
  }

  void arm_dom_node::add_succ (arm_dom_node* node) {
    succs.push_back(node);
    node->set_pred(this);
  }

  vector<arm_dom_node*>* arm_dom_node::get_succs (void) const {
    return &succs;
  }

  list<arm_dom_node*>* arm_dom_node::find_leafs (void) {
    list<arm_dom_node*>* l;
    if (succs.empty())
      return new list<arm_dom_node*> (1, this);
    else {
      l = new list<arm_dom_node*> ();
      for (auto& e:succs) {
	l->splice(l->end(), *e->find_leafs());
      }
      return l;
    }
  }

  void arm_dom_node::add_succ_vars (list<string>* vars) {
    this->succ_vars->splice(this->succ_vars->end(), *vars);
    delete vars;
    this->succ_vars->unique();
  }

}
