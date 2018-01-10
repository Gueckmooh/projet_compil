#include "arm_register_optimizer.h"
#include <functional>
#include <iostream>

namespace arm {

  arm_register_optimizer::arm_register_optimizer (arm_dom_node* dom_root) {
    this->dom_root = dom_root;
  }

  arm_dom_node* arm_register_optimizer::get_dom_root (void) {
    return dom_root;
  }

  void arm_register_optimizer::set_dom_root (arm_dom_node*) {
    this->dom_root = dom_root;
  }

  void arm_register_optimizer::optimize (void) {
    find_succs_variables (NULL);
    find_preds_variables (dom_root);
    find_variables (dom_root);
    find_variables_to_reduce (dom_root);
    auto print = [&](list<string>* l){for (auto& e: *l) cout << e << " "; cout << endl;};
    function<void(arm_dom_node*)> test = [&](arm_dom_node* node){print(node->get_variables_to_reduce()); for (auto& e: *node->get_succs()) test(e);};
    test(dom_root);
    optimize_node (dom_root);
  }

  void arm_register_optimizer::find_variables (arm_dom_node* node) {
    node->variables = node->element->get_vars();
    for (auto& e: (node->succs))
      find_variables (e);
  }

  void arm_register_optimizer::find_succs_variables (arm_dom_node* node) {
    list<string>* node_vars;
    if (node == NULL) {
      already_visited.clear();
      for (auto& node: *dom_root->find_leafs()) {
	node_vars = node->element->get_vars();
	if (node->pred != NULL)
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
	  node->succ_vars = node_vars;
	  already_visited.push_back(node);
	  node->pred->add_succ_vars (node_vars);
	}
      }
    }
  }

  void arm_register_optimizer::find_preds_variables (arm_dom_node* node) {
    list<string>* node_vars;
    node_vars = new list<string> (node->element->used_variables);
    if (node != dom_root)
      node_vars->splice(node_vars->end(), list<string>(*node->pred_vars));
    for (auto& n: node->succs) {
      n->pred_vars = node_vars;
      find_preds_variables(n);
    }
  }

  void arm_register_optimizer::find_variables_to_reduce (arm_dom_node* node) {
    node->variables_to_reduce = new list<string> ();
    auto in_leaf = [&](){bool ret = false;
			 for (auto& e: *dom_root->find_leafs())
			   ret |= e == node;
			 return ret;};
    for (auto& elt: *node->variables)
      if ([&](){bool ret = false;
	  if (!in_leaf())
	    for (auto& e: *node->succ_vars) ret |= e == elt;
	  if (node != dom_root)
	    for (auto& e: *node->pred_vars) ret |= e == elt;
	  return !ret;}()) node->variables_to_reduce->push_back (elt);
    for (auto& e: node->succs)
      find_variables_to_reduce(e);
  }

  /*
  void arm_register_optimizer::optimize_node (arm_dom_node* node) {
    int idx = 0;
    string reg;
    cout << node << " : ";
    auto in = [&](){
      bool ret = false;
      for (auto& e: *node->variables_to_reduce)
	ret |= e == f;
      return ret;};
    auto next_free = [&](){
      for (int i = 0; i < 5; i++)
	if ([&](){bool ret = false;
		  string str = "r" + string(i);
		  for (auto& e: node->element->regs_maps[idx])
		    ret |= e.first == str;
		  return !ret;})
	  return "r" + string(i);
      return "0";};
    for (auto& e: *node->variables_to_reduce)
      cout << e << " ";
    cout << endl;
    for (auto& e: node->element->var_instr) {
      for (auto& f: *e)
	cout << f << " ";
      cout << endl;
    }
    for (auto& e: node->element->var_instr) {
      for (auto& f: *e) {
	if (in()) {
	  reg = next_free();
	  if (reg != "0")
	    node->element->regs_maps[idx].insert(pair<string, string> (reg, f));
	}
      }
      idx++;
    }
  }
  */

  void arm_register_optimizer::optimize_node (arm_dom_node* node) {
    int idx = 0;
    string reg;
#ifdef __DEBUG
    cout << "in arm::arm_register_optimizer::optimize_node" << endl;
#endif
    for (auto& e: node->element->var_instr) {
      for (auto& f: *e) {
	if ([&](){bool ret = false;
	    for (auto& e: *node->variables_to_reduce)  // if we have to opimize var
	      ret |= e == f;
	    return ret;}()) {
#ifdef __DEBUG
	  cout << f << endl;
#endif
	  reg = [&](){
	    auto f = [&](int i){
	      bool ret = false;
	      string str = "r" + to_string(i);
	      for (auto& e: node->element->regs_maps[idx])
		ret |= e.first == str;
	      return !ret;};
	    for (int i = 0; i < 5; i++)
	      if (f(i))
		return "r" + to_string(i);
	    return string("0");}();
#ifdef __DEBUG
	  cout << reg << endl;
#endif
	  node->element->regs_maps[idx].insert(pair<string, string> (reg, f));
	}
      }
      idx++;
    }
  }

}
