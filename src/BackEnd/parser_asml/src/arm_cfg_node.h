#include <string>
#include <map>
#include <vector>
#include <list>

#ifndef __ARM_CFG_NODE_H__
#define __ARM_CFG_NODE_H__

#include "arm_cfg_element.h"

using namespace std;

namespace arm {

  class arm_cfg_node {
    friend class arm_cfg_factory;
    friend class arm_register_optimizer;
  public:
    void add_element (arm_cfg_element*);
    void find_vars (void);
    void add_succ (arm_cfg_node*);
    list<string>* get_vars (void);
    vector<arm_cfg_node*>* get_succs (void);
    vector<arm_cfg_node*>* get_preds (void);
  protected:
    void add_pred (arm_cfg_node*);
    vector<arm_cfg_node*> preds;
    vector<arm_cfg_node*> succs;
    vector<arm_cfg_element*> elements;
    vector<list<string>*> var_instr;
    list<string> used_variables;
    vector<map<string, string>> regs_maps;
    vector<map<string, int>> scope;
    int nb_regs;
  };

}

#endif //__ARM_CFG_NODE_H__
