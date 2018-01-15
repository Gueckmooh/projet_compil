#include <functional>
#include <boost/range/adaptor/reversed.hpp>

#ifndef __ARM_REGISTER_OPTIMIZER_H__
#define __ARM_REGISTER_OPTIMIZER_H__

#include "arm_dom_node.h"

using namespace std;

namespace arm {

  class arm_register_optimizer {
  public:
    arm_register_optimizer (void) {};
    arm_register_optimizer (arm_dom_node*);

    arm_dom_node* get_dom_root (void);
    void set_dom_root (arm_dom_node*);

    void optimize (void);
    void find_succs_variables (arm_dom_node*);
    void find_preds_variables (arm_dom_node*);
    void find_variables (arm_dom_node*);
    void find_variables_to_reduce (arm_dom_node*);
    void find_scope (arm_dom_node*);
    void optimize_node (arm_dom_node*);
  protected:
    arm_dom_node* dom_root;
    list<arm_dom_node*> already_visited;
  };

}

#endif//__ARM_REGISTER_OPTIMIZER_H__
