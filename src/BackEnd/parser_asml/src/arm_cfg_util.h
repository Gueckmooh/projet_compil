#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

#ifndef __ARM_CFG_UTIL_H__
#define __ARM_CFG_UTIL_H__

#include "arm_cfg_node.h"

using namespace std;

namespace arm {

  class arm_cfg_util {
  public:
    static void print_cfg (arm_cfg_node*);
  protected:
    static set<arm_cfg_node*> used;
  };

} // TODO

#endif//__ARM_CFG_UTIL_H__
