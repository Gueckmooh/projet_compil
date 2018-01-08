#include <string>
#include <list>
#include <vector>

#ifndef __ARM_DOM_NODE_H__
#define __ARM_DOM_NODE_H__

#include "arm_cfg_node.h"

using namespace std;

namespace arm {

  class arm_dom_node {
  public:
    arm_dom_node (void) {};
    arm_dom_node (arm_cfg_node*);
    void set_element (arm_cfg_node*);
    arm_cfg_node* get_element (void) const;
    void add_succ (arm_dom_node*);
    vector<arm_dom_node*>* get_succs (void) const;
  protected:
    arm_cfg_node* element;
    mutable vector<arm_dom_node*> succs;
    list<string>* variables;
  };

}

#endif//__ARM_DOM_NODE_H__
