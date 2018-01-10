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
#ifdef __DEBUG
    function<void(arm_dom_node*)> pscope = [&](arm_dom_node* node)->void{
      for (auto& e: node->element->scope) {
	cout << endl;
	for (auto& f: e)
	  cout << f.first << " : " << f.second << endl;
      }
    };
#endif
    find_succs_variables (NULL);
    find_preds_variables (dom_root);
    find_variables (dom_root);
    find_variables_to_reduce (dom_root);
#ifdef __DEBUG
    auto print = [&](list<string>* l){for (auto& e: *l) cout << e << " "; cout << endl;};
    function<void(arm_dom_node*)> test = [&](arm_dom_node* node){print(node->get_variables_to_reduce()); for (auto& e: *node->get_succs()) test(e);};
    test(dom_root);
#endif
    find_scope (dom_root);
    pscope (dom_root);
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
    auto in_leaf = [&](){
      bool ret = false;
      for (auto& e: *dom_root->find_leafs())
	ret |= e == node;
      return ret;
    };
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

  void arm_register_optimizer::find_scope (arm_dom_node* node) {
    map<string, int> current;
    auto var = node->element->var_instr.rbegin();
    auto scope = node->element->scope.rbegin();
    function<bool(string)> valid = [&](string var)->bool{
      bool ret = false;
      for (auto& e: *node->variables_to_reduce)
	ret |= var == e;
      return ret;
    };
    function<bool(string)> in_current = [&current](string var)->bool{
      return current.find(var)->first == var;
    };
    function<void(string)> inc = [&](string var) {
      int val = current.find(var)->second;
      current.erase(current.find(var));
      cout << val << endl;
      current.insert(pair<string, int>(var, val+1));
    };
    function<int(string)> process = [&](string var)->int{
      int val;
      if (in_current(var)) {
	inc(var);
	val = current.find(var)->second;
      } else {
	current.insert(pair<string, int>(var, 0));
	val = 0;
      }
      return val;
    };
    while (var != node->element->var_instr.rend()) {
      for (auto& e: **var)
	if (valid(e))
	  scope->insert(pair<string, int>(e, process(e)));
      var++;
      scope++;
    }
    for (auto& e: node->succs)
      find_scope(e);
  }

  void arm_register_optimizer::optimize_node (arm_dom_node* node) {
    int idx = 0;
    string reg;
    function<bool(int)> f = [&](int i)->bool{
      bool ret = false;
      string str = "r" + to_string(i);
      for (auto& e: node->element->regs_maps[idx])
	ret |= e.first == str;
      return !ret;
    };
    function<string(void)> fref = [&](void)->string{
      for (int i = 0; i < 5; i++)
	if (f(i))
	  return "r" + to_string(i);
      return string("0");
    };
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
	  reg = fref();
	  node->element->regs_maps[idx].insert(pair<string, string> (reg, f));
	  for (int i = 0; i < node->element->scope[idx].find(reg)->second; i++)
	    node->element->regs_maps[idx+i].insert(pair<string, string> (reg, f));
#ifdef __DEBUG
	  cout << reg << endl;
#endif
	}
      }
      idx++;
    }
  }

}
