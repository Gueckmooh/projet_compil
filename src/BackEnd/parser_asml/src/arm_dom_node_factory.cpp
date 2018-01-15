#include <iostream>
#include "arm_dom_node_factory.h"

namespace arm {

  arm_dom_node_factory::arm_dom_node_factory (arm_cfg_node* root) {
    cfg_root = root;
    dom_root = new arm_dom_node (cfg_root);
    node_eq.insert (pair<arm_cfg_node*, arm_dom_node*> (cfg_root, dom_root));
    get_succs(cfg_root);
  }

  void print_dom (arm_dom_node* root) {
#if defined __DEBUG && defined __VERBOSE
    cout << "arm::arm_dom_node_factory::prnt_dom" << endl;
    cout << root;
    for (auto& e: *root->get_succs())
      cout << " : " << e;
    cout << endl;
    for (auto& e: *root->get_succs())
      print_dom (e);
#endif
    return;
  }

  arm_dom_node* arm_dom_node_factory::generate (void) {
#if defined __DEBUG && defined __VERBOSE
    cout << "arm::arm_dom_node_factory::generate" << endl;
    for (auto& e: succs)
      cout << "[" << e.first << " : " << e.second << "]" << endl;
    cout << endl;
#endif
    arm_cfg_node* n = cfg_root;
    while (!n->get_succs()->empty())
      n = n->get_succs()->back();
    find_father(n);
#if defined __DEBUG && defined __VERBOSE
    set<path>* p = find_path(n);
    for (auto& e: *p) {
      for (auto& f: e)
	cout << f << " : ";
      cout << endl;
    }
#endif
    gen (cfg_root);
    //print_dom(dom_root);
    return dom_root;
  }

  void arm_dom_node_factory::gen (arm_cfg_node* node) {
    typedef pair<arm_cfg_node*, arm_dom_node*> eq;
    arm_dom_node* n;
    for (auto e: *node->get_succs()) {
      if (node_eq.find(e)->first != e) {
	n = new arm_dom_node (e);
	node_eq.find(find_father(e))->second->add_succ(n);
	node_eq.insert(eq(e, n));
      }
    }
    for (auto e: *node->get_succs()) {
      gen(e);
    }
  }

  set<arm_dom_node_factory::path>* arm_dom_node_factory::find_path (arm_cfg_node* node) {
    typedef arm_dom_node_factory::path path;
    bool has_pred = false;
    set<path> *p1, *p2;
    p1 = new set<path> ();
    for (auto& e: succs) {
      if (e.second == node) {
	has_pred = true;
	p2 = find_path (e.first);
	for (auto e: *p2) {
	  e.push_back(node);
	  p1->insert(e);
	}
      }
    }
    if (!has_pred)
      p1->insert(path(1,node));
    return p1;
  }

  bool arm_dom_node_factory::present (arm_cfg_node* node, set<arm_dom_node_factory::path>* s) {
    bool is_present = true;
    for (auto& e: *s) {
      is_present &= ([](auto e, auto n){
	bool ret = false;
	for (auto& p:e)
	  ret |= p==n;
	return ret;
      })(e, node);
    }
    return is_present;
  }

  arm_cfg_node* arm_dom_node_factory::find_father (arm_cfg_node* node) {
    typedef arm_dom_node_factory::path path;
    set<path> *paths = find_path (node);
    path p = *(paths->begin());
    auto it = p.rbegin()+1;
    while(!present(*it, paths)) {
      it++;
    }
#if defined __DEBUG && defined __VERBOSE
    cout << node << " : " << *it << endl;
#endif
    return *it;
  }

  void arm_dom_node_factory::get_succs (arm_cfg_node* node) {
    if ((*(already_visited.find (node))) != node) {
      already_visited.insert (node);
      for (auto& e: *node->get_succs()) {
	succs.insert (succ (node, e));
	get_succs (e);
      }
    }
  }

}
