#include <set>
#include <map>

#ifndef __ARM_DOM_NODE_FACTORY_H__
#define __ARM_DOM_NODE_FACTORY_H__

#include "arm_cfg_node.h"
#include "arm_dom_node.h"

using namespace std;

namespace arm {

  class arm_dom_node_factory {
  public:
    arm_dom_node_factory (arm_cfg_node*);
    arm_dom_node* generate (void);
  protected:
    void get_succs (arm_cfg_node*);
    map<arm_cfg_node*, arm_cfg_node*> succs;
    set<arm_cfg_node*> already_visited;
    arm_cfg_node* cfg_root;
    arm_dom_node* dom_root;
  };

}

#endif//__ARM_DOM_NODE_FACTORY_H__