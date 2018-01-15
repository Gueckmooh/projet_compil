#include <map>
#include <set>
#include <vector>

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
    typedef pair<arm_cfg_node*, arm_cfg_node*> succ;
    typedef vector<arm_cfg_node*> path;
    void gen (arm_cfg_node* node);
    bool present (arm_cfg_node*, set<path>*);
    set<path>* find_path (arm_cfg_node*);
    arm_cfg_node* find_father (arm_cfg_node*);
    void get_succs (arm_cfg_node*);
    set<succ> succs;
    set<arm_cfg_node*> already_visited;
    arm_cfg_node* cfg_root;
    arm_dom_node* dom_root;
    map<arm_cfg_node*, arm_dom_node*> node_eq;
  };

} // TODO

#endif//__ARM_DOM_NODE_FACTORY_H__
