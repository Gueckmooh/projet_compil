#include "arm_cfg_node.h"

namespace arm {

  void arm_cfg_node::add_element (arm_cfg_element* elt) {
    elements.push_back(elt);
  }

  list<string>* arm_cfg_node::get_vars (void) {
    return new list<string> (used_variables);
  }

  void arm_cfg_node::find_vars (void) {
    list<string>* l;
    if (used_variables.empty()) {
      for (vector<arm_cfg_element*>::iterator it = elements.begin();
	   it != elements.end();
	   it++) {
	l = (*it)->get_vars();
	used_variables.merge(*l);
	delete l;
      }
      used_variables.sort();
      used_variables.unique();
    }
  }

  void arm_cfg_node::add_succ (arm_cfg_node* succ) {
    succs.push_back(succ);
    succ->add_pred(this);
  }

  void arm_cfg_node::add_pred (arm_cfg_node* pred) {
    preds.push_back(pred);
  }

  vector<arm_cfg_node*>* arm_cfg_node::get_succs (void) {
    return &succs;
  }

  vector<arm_cfg_node*>* arm_cfg_node::get_preds (void) {
    return &preds;
  }

}