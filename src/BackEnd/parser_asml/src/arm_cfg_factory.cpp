#include "arm_cfg_factory.h"

namespace arm {

  arm_cfg_node* arm_cfg_factory::generate_cfg (vector<arm_instruction*>* instructions) {
    return generate_cfg_node (instructions);
  }

  arm_cfg_node* arm_cfg_factory::generate_cfg_node (vector<arm_instruction*>* instructions) {
    arm_cfg_node* node = new arm_cfg_node ();
    arm_cfg_node* current = node;
    arm_cfg_node* lnode,* rnode;
    arm_cfg_element* element;
    for (vector<arm_instruction*>::iterator it = instructions->begin();
         it != instructions->end();
         it++) {
      if ((*it)->get_type() == arm_instruction::CONDITION) {
        element = new arm_cfg_element (*it);
        current->add_element (element);
        lnode = generate_cfg_node (dynamic_cast<arm_condition*>(*it)->get_list_then());
        rnode = generate_cfg_node (dynamic_cast<arm_condition*>(*it)->get_list_else());
        current->add_succ (lnode);
        current->add_succ (rnode);
        current = new arm_cfg_node ();
        lnode->add_succ(current);
        rnode->add_succ(current);
      } else {
        element = new arm_cfg_element (*it);
        current->add_element (element);
      }
    }
    return node;
  }

}
