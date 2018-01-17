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
    function<void(arm_dom_node*)> find_vars = [&](arm_dom_node* node){
      node->element->find_vars();
      for (auto& e: node->succs)
	find_vars(e);
    };
    #if defined __DEBUG && defined __VERBOSE
    function<void(arm_dom_node*)> pscope = [&](arm_dom_node* node)->void{
      for (auto& e: node->element->scope) {
        cout << endl;
        for (auto& f: e)
          cout << f.first << " : " << f.second << endl;
      }
    };
    #endif
    find_vars(dom_root);
    find_succs_variables (NULL);
    find_preds_variables (dom_root);
    find_variables (dom_root);
    find_variables_to_reduce (dom_root);
    #if defined __DEBUG && defined __VERBOSE
    auto print = [&](list<string>* l){for (auto& e: *l) cout << e << " "; cout << endl;};
    function<void(arm_dom_node*)> test = [&](arm_dom_node* node){print(node->get_variables_to_reduce()); for (auto& e: *node->get_succs()) test(e);};
    test(dom_root);
    #endif
    find_scope (dom_root);
    #if defined __DEBUG && defined __VERBOSE
    pscope (dom_root);
    #endif
    optimize_node (dom_root);
    #if defined __DEBUG
    function<void(arm_dom_node*)> p_afterop = [&](arm_dom_node* node){
      cout << "Node " << node << " :" <<endl << endl;
      for (auto& e: node->element->regs_maps) {
	for (auto& f: e)
	  cout << f.first << " : " << f.second << endl;
	cout << endl;
      }
      for (auto& e: node->succs)
	p_afterop (e);
    };
    p_afterop (dom_root);
    #endif
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

  /*
  void arm_register_optimizer::find_scope (arm_dom_node* node) {
    map<string, int> current;
    auto var = node->element->var_instr.rbegin();
    auto scope = node->element->scope.rbegin();
    function<bool(string)> valid;
    function<bool(string)> in_current;
    function<void(string)> inc;
    function<int(string)> process;
    // Definition of lambdas expressions
    valid = [&](string var)->bool{
      bool ret = false;
      for (auto& e: *node->variables_to_reduce)
        ret |= var == e;
      return ret;
    };
    in_current = [&current](string var)->bool{
      return current.find(var)->first == var;
    };
    inc = [&](string var) {
      int val = current.find(var)->second;
      current.erase(current.find(var));
      current.insert(pair<string, int>(var, val+1));
    };
    process = [&](string var)->int{
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
    // end of definition
    while (var != node->element->var_instr.rend()) {
      for (auto& e: **var)
        if (valid(e))
          scope->insert(pair<string, int>(e, process(e)));
      var++;
      scope++;
    }
    cout << var << " : " <<
    for (auto& e: node->succs)
      find_scope(e);
  }
  */

  void arm_register_optimizer::find_scope (arm_dom_node* node) {
    // Variables definition
    typedef pair<string, int> spair;
    typedef map<string, int> smap;
    function<bool(string)> can_be_optimized;
    function<void(string)> set_scope;
    function<int(string)> increment;
    auto vars = node->element->var_instr.rbegin();
    auto scope = node->element->scope.rbegin();
    smap current;

    { // Lambdas initialisation
      can_be_optimized = [&node](string var)->bool {
	bool ret = false;
	for (auto& elt: *node->variables_to_reduce)
	  ret |= elt == var;
	return ret;
      };
      set_scope = [&scope, &increment](string var)->void {
	int val = increment(var);
	scope->insert(spair(var, val));
      };
      increment = [&current](string var)->int {
        auto elt = current.find(var);
	int val;
	if (elt->first == var) {
	  val = (elt->second)+1;
	  current.erase(elt);
	} else val = 0;
	current.insert(spair(var, val));
	return val;
      };
    }

    { // Body
      while (vars != node->element->var_instr.rend()) {
	for (auto& var: **vars) {
	  if (can_be_optimized(var))
	    set_scope(var);
	}
	vars++;
	scope++;
      }
      for (auto& e: node->succs)
	find_scope (e);
    }
  }

  void arm_register_optimizer::optimize_node (arm_dom_node* node) {
    int index = 0;
    function<bool(string)> can_be_optimized;
    function<void(string, string)> propagate;
    function<string(string)> process;
    function<int(string)> get_scope;
    function<string(string)> free_reg;
    function<int(vector<list<string>*>::iterator)> get_max_scope;
    // Definitions of lambdas
    can_be_optimized = [&](string var)->bool{
      bool ret = false;
      for (auto& e: *node->variables_to_reduce)
        ret |= e == var;
      return ret;
    };
    propagate = [&](string var, string reg) {
      for (int i = 0; i <= node->element->scope[index].find(var)->second; i++)
        node->element->regs_maps[index+i].insert(pair<string, string> (reg, var));
    };
    process = [&](string var)->string{
      auto reg = free_reg(var);
      auto current = node->element->regs_maps[index];
      current.insert(pair<string, string>(var, reg));
      cout << "Processes " << reg << endl;
      return reg;
    };
    get_scope = [&](string var)->int{
      auto scopes = node->element->scope[index];
      int scope = scopes.find(var)->second;
      cout << "Scope " << scope << endl;
      return scope;
    };
    get_max_scope = [&](vector<list<string>*>::iterator vars)->int{
      int ret = 0;
      int idx = node->element->var_instr.begin() - vars;
      while ((int)(node->element->nb_regs[idx] - node->element->regs_maps[idx].size()) > 0) {
	
	cout << "node->element->nb_regs[idx] : " << node->element->nb_regs[idx] << endl;
	cout << "node->element->regs_maps[idx].size() : " << node->element->regs_maps[idx].size() << endl;
	cout << "node->element->nb_regs[idx] - node->element->regs_maps[idx].size() : " <<
	  node->element->nb_regs[idx] - node->element->regs_maps[idx].size() << endl;
        ret++;
        idx++;
      }
      ret = ret == 0 ? 0 : ret-1;
      cout << "Max scope " << ret << endl;
      return ret;
    };
    free_reg = [&](string var)->string{
      auto current = node->element->regs_maps[index];
      int reg = 0;
      auto stringify = [](auto r){return "r" + to_string(r);};
      auto already_in = [&](string str)->bool{
	bool ret = false;
	for (auto& elt: current)
	  ret |= elt.second == str;
	return ret;
      };
      if (!already_in(var))
	while (current.find(stringify(reg))->first == stringify(reg))
	  if (current.find(stringify(reg))->second == var)
	    break;
	  else
	    reg++;
      else
	for (auto& e: current)
	  if (e.second == var)
	    return e.first;
      cout << stringify(reg) << endl;;
      return stringify(reg);
    };
    // End of lambdas definitions
    for (vector<list<string>*>::iterator vars = node->element->var_instr.begin();
         vars != node->element->var_instr.end();
         vars++) {
      for (auto& var: **vars) {
	cout << var << " :" << endl;
        if (can_be_optimized (var)) {
	  /*
	  cout << "get_scope(var) : " << get_scope(var) << endl;
	  cout << "get_max_scope(vars) : " << get_max_scope(vars) << endl;
	  cout << "get_scope(var) <= get_max_scope(vars) : " << (get_scope(var) <= get_max_scope(vars)) << endl;
	  */
          if (get_scope(var) <= get_max_scope(vars)) {
            propagate (var, process (var));
          }
        }
      }
      index++;
    }
  }


}
