#include <string>
#include <vector>
#include <list>
#include <map>

#ifndef __ARM_CFG_FACTORY_H__
#define __ARM_CFG_FACTORY_H__

#include "arm_cfg_node.h"
#include "arm_instruction.h"
#include "arm_condition.h"

using namespace std;

namespace arm {

  class arm_cfg_factory {
  public:
    static arm_cfg_node* generate_cfg (vector<arm_instruction*>*);
  protected:
    static arm_cfg_node* generate_cfg_node (vector<arm_instruction*>*);
    static arm_cfg_node* root;
  };

}

#endif//__ARM_CFG_FACTORY_H__
