#include <string>
#include <list>
#include <vector>

#ifndef __ARM_DOM_NODE_H__
#define __ARM_DOM_NODE_H__

#include "arm_cfg_node.h"

using namespace std;

namespace arm {

  class arm_dom_node {
    friend class arm_regster_optimizer;
  public:
    arm_dom_node (void) {};
    arm_dom_node (arm_cfg_node*);
    void set_element (arm_cfg_node*);
    arm_cfg_node* get_element (void) const;
    void add_succ (arm_dom_node*);
    vector<arm_dom_node*>* get_succs (void) const;
    list<arm_dom_node*>* find_leafs (void);
    void add_succ_vars (list<string>*);
  protected:
    void set_pred (arm_dom_node* node);
    list<string>* succ_vars;
    arm_cfg_node* element;
    mutable vector<arm_dom_node*> succs;
    mutable arm_dom_node* pred;
    list<string>* variables;
  };

}

#endif//__ARM_DOM_NODE_H__
