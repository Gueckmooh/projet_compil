#include "arm_cfg_util.h"

namespace arm {

  set<arm_cfg_node*> arm_cfg_util::used;

  void print_vars (list<string>* vars) {
    #if defined __DEBUG && defined __VERBOSE
    cout << "arm::arm_cfh_util::print_vars" << endl;
    for (list<string>::iterator it = vars->begin();
	 it != vars->end();
	 it++) {
      cout << (*it) << "; ";
    }
    cout << endl;
    #endif
    return;
  }

  void arm_cfg_util::print_cfg (arm_cfg_node* node) {
#if defined __DEBUG && defined __VERBOSE
    cout << "arm::arm_cfg_util::print_cfg" << endl;
    arm_cfg_node* current = node;
    if ((*(used.find(current))) != current) {
      used.insert (current);
      cout << current << endl;
      cout << "Childrens : ";
      for (vector<arm_cfg_node*>::iterator it = (current->get_succs())->begin();
	   it != current->get_succs()->end();
	   it++) {
	cout << (*it) << "; ";
      }
      cout << endl;
      current->find_vars();
      print_vars (current->get_vars());
      for (vector<arm_cfg_node*>::iterator it = current->get_succs()->begin();
	   it != current->get_succs()->end();
	   it++) {
	print_cfg(*it);
      }
      cout << endl;
    }
#endif
    return;
  }

}
